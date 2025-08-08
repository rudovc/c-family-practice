#include <asm-generic/errno-base.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "lib/arena.h"
#include "lib/error.h"
#include "lib/heaparray.h"
#include "lib/input.h"
#include "lib/str.h"

static const int32_t INPUT_BUFFER_SIZE = 16;
static const ptrdiff_t REVERSE_INPUT_ARRAY_BUFFER = 128 * sizeof(int16_t);

enum task {
        PRINT_USER_INPUT_TASK,
        REVERSE_ARRAY_TASK,
        TWOD_ARRAY_TASK,
        DYNAMIC_ARRAY_TASK,
        LINKED_LIST_TASK,
        DOUBLY_LINKED_LIST_TASK
};

static const char* const OPTIONS[] = {
        "print", "reverse", "2d-array", "dynamic", "linked", "doubly-linked"};

int main()
{
        MaybeArenaAllocator maybe_arena =
                try_new_arena_allocator(INPUT_BUFFER_SIZE + (REVERSE_INPUT_ARRAY_BUFFER * 2));

        if (!maybe_arena.exists) {
                print_error("Failed to create allocator");

                return 1;
        }

        ArenaAllocator arena = maybe_arena.item;

        MaybeString maybe_input = take_user_input_stdin(INPUT_BUFFER_SIZE, &arena);

        if (!maybe_input.exists) {
                print_error("Failed to take user input");

                return 1;
        }

        String input_string = maybe_input.item;
        char* input = input_string.str;

        int compare_output = strcmp(input, OPTIONS[PRINT_USER_INPUT_TASK]);

        if (compare_output == 0) {
                printf("Hello, world!");
        }

        if (strcmp(input, OPTIONS[REVERSE_ARRAY_TASK]) == 0) {
                printf("Input a space separated sequence of numbers:\n");
                maybe_input = take_user_input_stdin(INPUT_BUFFER_SIZE, &arena);

                if (!maybe_input.exists) {
                        print_error("Failed to take user input");

                        return 1;
                }

                MaybeStringArray split_input = split_string_on_char(&maybe_input.item, &arena, ' ');

                for_each_in_StringArray(&split_input.item, println_string);

                Int16Array input_int_array = new_Int16Array(4, &arena);

                input_int_array.arr[0] = 1;
                input_int_array.arr[1] = 4;
                input_int_array.arr[2] = 3;
                input_int_array.arr[3] = 2;

                MaybeInt16Array output_maybe_int_array =
                        reverse_int16_array(&input_int_array, &arena);

                if (!output_maybe_int_array.exists) {
                        free_arena(arena);

                        return 1;
                }

                // Int16Array output_int_array = unwrap_MaybeInt16Array(output_maybe_int_array);

                // for (int i = 0; i < output_int_array.len; i++) {
                //         printf("%d\n", output_int_array.arr[i]);
                // }
        }

        free_arena(arena);

        return 0;
}
