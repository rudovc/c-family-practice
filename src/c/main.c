#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/arena.h"
#include "lib/error.h"
#include "lib/heaparray.h"
#include "lib/input.h"
#include "lib/str.h"

static const int32_t INPUT_BUFFER_SIZE = 512;
static const ptrdiff_t REVERSE_INPUT_ARRAY_BUFFER = 256 * sizeof(int16_t);
static const int8_t RADIX_BASE_10 = 10;

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

                if (!split_input.exists) {
                        print_error("Failed to split input string into parts");

                        return 1;
                }

                Int16Array input_int_array = new_Int16Array(0, &arena);

                for (int i = 0; i < split_input.item.len; ++i) {
                        char* substring = new_cstring_from_string(&split_input.item.arr[i], &arena);

                        int16_t number = (int16_t)strtol(substring, NULL, RADIX_BASE_10);

                        input_int_array = grow_by_Int16Array(
                                &input_int_array, input_int_array.len + 1, &arena);

                        input_int_array.arr[input_int_array.len - 1] = number;
                }

                MaybeInt16Array output_maybe_int_array =
                        reverse_int16_array(&input_int_array, &arena);

                if (!output_maybe_int_array.exists) {
                        free_arena(arena);

                        return 1;
                }

                Int16Array output_int_array = unwrap_MaybeInt16Array(output_maybe_int_array);

                for (int i = 0; i < output_int_array.len; i++) {
                        printf("%d\n", output_int_array.arr[i]);
                }
        }

        free_arena(arena);

        return 0;
}
