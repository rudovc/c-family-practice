#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "arena.h"
#include "error.h"
#include "str.h"

MaybeString take_user_input_stdin(int32_t buffer_size_in_bytes, ArenaAllocator* allocator)
{
        MaybePointer maybe_buffer =
                try_allocate_to_arena(buffer_size_in_bytes, allocator, DEFAULT_ALIGNMENT);

        if (!maybe_buffer.exists) {
                return new_nothing_MaybeString();
        }

        char* buffer = maybe_buffer.item;

        char* status = fgets(buffer, buffer_size_in_bytes, stdin);

        if (status == NULL) {
                perror("Error:");

                return new_nothing_MaybeString();
        }

        size_t len = strlen(buffer);

        if (len > INT32_MAX) {
                print_error("Requested buffer is larger than maximum allowed length.");

                return new_nothing_MaybeString();
        }

        // Strip whitespace from fgets buffer
        buffer[len - 1] = 0;

        String string = {.len = len - 1, .str = buffer};

        return new_exists_MaybeString(string);
}
