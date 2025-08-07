#pragma once

#include <stddef.h>
#include <stdint.h>

#include "arena.h"
#include "maybe.h"

#define DECLARE_HEAP_ARRAY(T, N) \
        typedef struct { \
                T* arr; \
                int32_t len; \
        } N; \
        N new_##N(int32_t len, ArenaAllocator* allocator);

DECLARE_HEAP_ARRAY(int32_t, Int32Array)
DECLARE_HEAP_ARRAY(int16_t, Int16Array)

#define IMPLEMENT_HEAP_ARRAY(T, N) \
        N new_##N(int32_t len, ArenaAllocator* allocator) \
        { \
                uintptr_t size_in_bytes = len * sizeof(T); \
                if (size_in_bytes > INT32_MAX) { \
                        print_error("Requested ##N  is larger than maximum allowed length."); \
                        free_arena(*allocator); \
                        abort(); \
                } \
                T* start = allocate_to_arena(len, allocator, DEFAULT_ALIGNMENT); \
                N array = {.arr = start, .len = len}; \
                return array; \
        } \
        N grow_##N(int32_t len, ArenaAllocator* allocator) \
        { \
                uintptr_t size_in_bytes = len * sizeof(T); \
                if (size_in_bytes > INT32_MAX) { \
                        print_error("Requested ##N  is larger than maximum allowed length."); \
                        free_arena(*allocator); \
                        abort(); \
                } \
                T* start = allocate_to_arena(len, allocator, DEFAULT_ALIGNMENT); \
                N array = {.arr = start, .len = len}; \
                return array; \
        }

#define DECLARE_MAYBE_HEAP_ARRAY(N, M) M try_new_##N(int32_t len, ArenaAllocator* allocator);

#define IMPLEMENT_MAYBE_HEAP_ARRAY(N, M) \
        M try_new##N(int32_t len, ArenaAllocator* allocator) \
        { \
                uintptr_t size_in_bytes = len * sizeof(T); \
                if (size_in_bytes > INT32_MAX) { \
                        print_error("Requested ##N is larger than maximum allowed length."); \
                        return new_nothing_##N(); \
                } \
                MaybePointer maybe_start = \
                        try_allocate_to_arena(len, allocator, DEFAULT_ALIGNMENT); \
                if (!maybe_start.exists) \
                        return new_nothing_##M(); \
                N* start = maybe_start.item; \
                N array = {.arr = start, .len = len}; \
                return new_exists_##M(array); \
        }

/** void for_each_in_##N(N array, (void*)(T element)callback) \
{ \
        (T*)arr = array->arr; \
        for (int i = 0; i < array->len; i++) { \
                callback(arr[i]); \
        } \
}*/

MAYBE(Int32Array) MaybeInt32Array;
DECLARE_UNWRAP(MaybeInt32Array, Int32Array)
DECLARE_NEW_NOTHING(MaybeInt32Array)
DECLARE_NEW_EXISTS(MaybeInt32Array, Int32Array)

MaybeInt32Array reverse_int32_array(Int32Array* array, ArenaAllocator* allocator);

MAYBE(Int16Array) MaybeInt16Array;
DECLARE_UNWRAP(MaybeInt16Array, Int16Array)
DECLARE_NEW_NOTHING(MaybeInt16Array)
DECLARE_NEW_EXISTS(MaybeInt16Array, Int16Array)

MaybeInt16Array reverse_int16_array(Int16Array* array, ArenaAllocator* allocator);
