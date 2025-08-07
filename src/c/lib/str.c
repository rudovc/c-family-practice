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
                try_allocate_to_arena(size_in_bytes, allocator, DEFAULT_ALIGNMENT));
        String string = {.str = start, .len = len};

        return new_exists_MaybeString(string);
}

MaybeString new_string_from_cstring(int32_t len, ArenaAllocator* allocator, const char* contents)
{
        uintptr_t size_in_bytes = len * sizeof(char);

        if (size_in_bytes > INT32_MAX) {
                print_error("Requested string is larger than maximum allowed length.");

                return new_nothing_MaybeString();
        }

        char* start = unwrap_MaybePointer(
                try_allocate_to_arena(size_in_bytes, allocator, DEFAULT_ALIGNMENT));
        start = strcpy(start, contents);
        String string = {.str = start, .len = len};

        return new_exists_MaybeString(string);
}

MaybeString reverse_string(String* string, ArenaAllocator* allocator)
{
        String new_char_arr = unwrap_MaybeString(new_empty_string(string->len, allocator));

        for (int i = 0; i < string->len; ++i) {
                new_char_arr.str[(string->len - 1) - i] = string->str[i];
        }

        return new_exists_MaybeString(new_char_arr);
}

MaybeStringArray split_string_on_char(String* string, ArenaAllocator* allocator, char delimiter)
{
        size_t size_of_string_in_bytes = string->len * sizeof(char);

        if (size_of_string_in_bytes > PTRDIFF_MAX) {
                print_error("Tried to perform split operation on string that's too long");

                return new_nothing_MaybeStringArray();
        }

        char str_char = 0;
        int buffer_i = 0;
        char* buffer = unwrap_MaybePointer(
                try_allocate_to_arena(size_of_string_in_bytes, allocator, DEFAULT_ALIGNMENT));
        MaybeStringArray string_array = new_nothing_MaybeStringArray();

        for (int i = 0; i < string->len; i++) {
                str_char = string->str[i];

                // If we're on the delimiter, set a null byte in its place so we can use strcpy
                if (str_char == delimiter) {
                        buffer[i] = 0;
                        size_t buffer_len = strlen(buffer);

                        if (buffer_len > INT32_MAX) {
                                print_error(
                                        "Requested string is larger than maximum allowed length.");

                                return new_nothing_MaybeStringArray();
                        }

                        if (string_array.exists) {
                                int32_t len = string_array.item.len;
                                string_array.item.len = len + 1;
                                string_array.item.arr[len] = unwrap_MaybeString(
                                        new_string_from_cstring(strlen(buffer), allocator, buffer));
                        } else {
                                string_array.item = new_StringArray(1, allocator);
                                string_array.item.len = 1;
                                string_array.item.arr[0] = unwrap_MaybeString(
                                        new_string_from_cstring(strlen(buffer), allocator, buffer));
                                string_array.exists = EXISTS;
                        }

                        buffer_i = 0;
                } else {
                        // Else just continue copying the string to the buffer
                        buffer[buffer_i] = str_char;
                        buffer_i++;
                }
        }

        return string_array;
}
