#include "heaparray.h"

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "arena.h"
#include "error.h"
#include "maybe.h"

IMPLEMENT_HEAP_ARRAY(int32_t, Int32Array)

IMPLEMENT_UNWRAP(MaybeInt32Array, Int32Array)
IMPLEMENT_NEW_NOTHING(MaybeInt32Array)
IMPLEMENT_NEW_EXISTS(MaybeInt32Array, Int32Array)

MaybeInt32Array reverse_int32_array(Int32Array* array, ArenaAllocator* allocator)
{
        // TODO: Replace with try_new_array
        int32_t arr_size_in_bytes = array->len * sizeof(int32_t);
        MaybePointer maybe_start = try_allocate_to_arena(arr_size_in_bytes, allocator, DEFAULT_ALIGNMENT);
        if (!maybe_start.exists) {
                return new_nothing_MaybeInt32Array();
        }

        int32_t* start = maybe_start.item;

        Int32Array new_int_arr = new_Int32Array(array->len, allocator);

        if (start == NULL) {
                errno = ENOMEM;
                perror("Error:");

                return new_nothing_MaybeInt32Array();
        }

        for (int i = 0; i < array->len; ++i) {
                new_int_arr.arr[(array->len - 1) - i] = array->arr[i];
        }

        return new_exists_MaybeInt32Array(new_int_arr);
}

IMPLEMENT_HEAP_ARRAY(int16_t, Int16Array)

IMPLEMENT_UNWRAP(MaybeInt16Array, Int16Array)
IMPLEMENT_NEW_NOTHING(MaybeInt16Array)
IMPLEMENT_NEW_EXISTS(MaybeInt16Array, Int16Array)

MaybeInt16Array reverse_int16_array(Int16Array* array, ArenaAllocator* allocator)
{
        // TODO: Replace with try_new_array
        int16_t arr_size_in_bytes = array->len * sizeof(int16_t);
        MaybePointer maybe_start = try_allocate_to_arena(arr_size_in_bytes, allocator, DEFAULT_ALIGNMENT);
        if (!maybe_start.exists) {
                return new_nothing_MaybeInt16Array();
        }

        int16_t* start = maybe_start.item;

        Int16Array new_int_arr = new_Int16Array(array->len, allocator);

        if (start == NULL) {
                errno = ENOMEM;
                perror("Error:");

                return new_nothing_MaybeInt16Array();
        }

        for (int i = 0; i < array->len; ++i) {
                new_int_arr.arr[(array->len - 1) - i] = array->arr[i];
        }

        return new_exists_MaybeInt16Array(new_int_arr);
}
