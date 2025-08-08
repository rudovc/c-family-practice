#include "str.h"

#include <asm-generic/errno-base.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arena.h"
#include "error.h"
#include "heaparray.h"
#include "maybe.h"

IMPLEMENT_UNWRAP(MaybeString, String);
IMPLEMENT_NEW_NOTHING(MaybeString);
IMPLEMENT_NEW_EXISTS(MaybeString, String);

IMPLEMENT_HEAP_ARRAY(String, StringArray)

IMPLEMENT_UNWRAP(MaybeStringArray, StringArray)
IMPLEMENT_NEW_NOTHING(MaybeStringArray)
IMPLEMENT_NEW_EXISTS(MaybeStringArray, StringArray)

IMPLEMENT_UNWRAP(MaybeStringArrayPointer, MaybeStringArray*)
IMPLEMENT_NEW_NOTHING(MaybeStringArrayPointer)
IMPLEMENT_NEW_EXISTS(MaybeStringArrayPointer, MaybeStringArray*)

String copy_string(String* string, ArenaAllocator* allocator)
{
        char* start = unwrap_MaybePointer(
                try_allocate_to_arena(string->len, allocator, DEFAULT_ALIGNMENT));
        String new_string = {.str = start, .len = string->len};

        return new_string;
}

MaybeString new_empty_string(int32_t len, ArenaAllocator* allocator)
{
        uintptr_t size_in_bytes = len * sizeof(char);

        if (size_in_bytes > INT32_MAX) {
                print_error("Requested string is larger than maximum allowed length.");

                return new_nothing_MaybeString();
        }

        char* start = unwrap_MaybePointer(
                try_allocate_to_arena((ptrdiff_t)size_in_bytes, allocator, DEFAULT_ALIGNMENT));
        String string = {.str = start, .len = len};

        return new_exists_MaybeString(string);
}

char* new_cstring_from_string(String* string, ArenaAllocator* allocator)
{
        char* cstring_start = unwrap_MaybePointer(
                try_allocate_to_arena((ptrdiff_t)string->len + 1, allocator, DEFAULT_ALIGNMENT));

        memcpy(cstring_start, string->str, string->len);

        cstring_start[string->len] = '\0';

        return cstring_start;
}

void print_string(String* string)
{
        for (int i = 0; i < string->len; ++i) {
                printf("%c", string->str[i]);
        }
}

void println_string(String* string)
{
        for (int i = 0; i < string->len; ++i) {
                printf("%c", string->str[i]);
        }

        printf("\n");
}

/*
 * This function could just take a destination pointer instead of the allocator and then it would be
 * more performant to use in the split_string function, but I'm just trying to have some fun.
 * Squeezing for performance comes when you actually know what you're doing
 */
MaybeString new_string_from_bytes(int32_t len, ArenaAllocator* allocator, const char* contents)
{
        uintptr_t size_in_bytes = len * sizeof(char);

        if (size_in_bytes > INT32_MAX) {
                print_error("Requested string is larger than maximum allowed length.");

                return new_nothing_MaybeString();
        }

        char* start = unwrap_MaybePointer(
                try_allocate_to_arena((ptrdiff_t)size_in_bytes, allocator, DEFAULT_ALIGNMENT));
        start = memcpy(start, contents, size_in_bytes);
        String string = {.str = start, .len = len};

        return new_exists_MaybeString(string);
}

MaybeString reverse_string(String* string, ArenaAllocator* allocator)
{
        String new_char_arr = unwrap_MaybeString(new_empty_string(string->len, allocator));

        for (int32_t i = 0; i < string->len; ++i) {
                new_char_arr.str[(string->len - 1) - i] = string->str[i];
        }

        return new_exists_MaybeString(new_char_arr);
}

void initialize_maybe_string_array(MaybeStringArray* maybe_string_array,
                                   String string,
                                   char* str_address)
{
        maybe_string_array->exists = EXISTS;
        maybe_string_array->item.len = 1;

        String new_string = {.len = string.len, .str = str_address};
        maybe_string_array->item.arr[0] = new_string;

        memcpy(maybe_string_array->item.arr[0].str, string.str, string.len);
}

MaybeStringArray split_string_on_char(String* string, ArenaAllocator* allocator, char delimiter)
{
        size_t total_max_size_of_string = string->len;
        size_t total_max_size_of_strings = string->len * sizeof(String);
        size_t total_max_size_of_buffer = (size_t)string->len * 2;

        if (total_max_size_of_string > PTRDIFF_MAX || total_max_size_of_buffer > PTRDIFF_MAX) {
                print_error("Requested string buffer is larger than maximum allowed length.");

                return new_nothing_MaybeStringArray();
        }

        ArenaAllocator buffer_arena = unwrap_MaybeArenaAllocator(try_new_arena_allocator(
                (ptrdiff_t)(total_max_size_of_buffer + total_max_size_of_strings)));

        String* string_pointers_buffer = unwrap_MaybePointer(
                try_allocate_to_arena((ptrdiff_t)total_max_size_of_strings, &buffer_arena, 1));

        StringArray* output_string_array = unwrap_MaybePointer(
                try_allocate_to_arena(sizeof(StringArray), allocator, DEFAULT_ALIGNMENT));

        output_string_array->len = 0;
        output_string_array->arr = string_pointers_buffer;

        void* string_array_chars_start = unwrap_MaybePointer(try_allocate_to_arena(
                (ptrdiff_t)total_max_size_of_string, allocator, DEFAULT_ALIGNMENT));

        int32_t string_length = string->len;

        char* char_buffer = unwrap_MaybePointer(
                try_allocate_to_arena((ptrdiff_t)total_max_size_of_buffer, &buffer_arena, 1));
        int32_t char_buffer_i = 0;

        for (int32_t i = 0; i < string_length; ++i) {
                char current_char = string->str[i];

                if (current_char == delimiter || i == string_length - 1) {
                        if (current_char == delimiter) {
                                char_buffer[char_buffer_i] = 0;
                        } else {
                                char_buffer[char_buffer_i + 1] = 0;
                                char_buffer[char_buffer_i] = current_char;
                        }

                        int32_t buffer_len = (int32_t)strlen(char_buffer);
                        String* temp_string = unwrap_MaybePointer(try_allocate_to_arena(
                                sizeof(String), allocator, DEFAULT_ALIGNMENT));

                        temp_string->len = buffer_len;

                        if (output_string_array->len > 0) {
                                int32_t prev_substring_index = output_string_array->len - 1;
                                int32_t new_substring_index = output_string_array->len++;
                                int32_t prev_substring_len =
                                        output_string_array->arr[prev_substring_index].len;

                                void* prev_substring_start =
                                        output_string_array->arr[prev_substring_index].str;
                                void* new_substring_start =
                                        prev_substring_start + prev_substring_len;

                                temp_string->str = new_substring_start;

                                output_string_array->arr[new_substring_index] = *temp_string;
                                output_string_array->arr[new_substring_index].len = buffer_len;
                                output_string_array->arr[new_substring_index].str =
                                        memcpy(new_substring_start, char_buffer, buffer_len);
                        } else {
                                temp_string->str = string_array_chars_start;

                                output_string_array->len = 1;
                                output_string_array->arr[0] = *temp_string;
                                output_string_array->arr[0].str =
                                        memcpy(string_array_chars_start, char_buffer, buffer_len);
                        }

                        char_buffer_i = 0;
                } else {
                        char_buffer[char_buffer_i] = current_char;
                        ++char_buffer_i;
                }
        }

        String* output_string_pointers = unwrap_MaybePointer(try_allocate_to_arena(
                (ptrdiff_t)total_max_size_of_strings, allocator, DEFAULT_ALIGNMENT));

        memcpy(output_string_pointers,
               string_pointers_buffer,
               sizeof(String) * output_string_array->len);

        output_string_array->arr = output_string_pointers;

        free_arena(buffer_arena);

        return new_exists_MaybeStringArray(*output_string_array);
}
