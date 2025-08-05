#pragma once

#include <stddef.h>
#include <stdint.h>

#include "arena.h"
#include "maybe.h"
#include "str.h"

#define DECLARE_HEAP_ARRAY(T, N) \
        typedef struct { \
                T* arr; \
                int32_t len; \
        } N; \
        N new_##N(int32_t len, T* start);

DECLARE_HEAP_ARRAY(int32_t, Int32Array)

#define IMPLEMENT_HEAP_ARRAY(T, N) \
        N new_##N(int32_t len, T* start) \
        { \
                N int_array = {.arr = start, .len = len}; \
                return int_array; \
        }

DECLARE_HEAP_ARRAY(String, StringArray)

int32_t calculate_size_of_int32_array(int len);

MAYBE(Int32Array) MaybeInt32Array;
DECLARE_UNWRAP(MaybeInt32Array, Int32Array)
DECLARE_NEW_NOTHING(MaybeInt32Array)
DECLARE_NEW_EXISTS(MaybeInt32Array, Int32Array)

MAYBE(StringArray) MaybeStringArray;
DECLARE_UNWRAP(MaybeStringArray, StringArray);
DECLARE_NEW_NOTHING(MaybeStringArray);
DECLARE_NEW_EXISTS(MaybeStringArray, StringArray);

MaybeInt32Array reverse_int32_array(Int32Array* array, ArenaAllocator* allocator);
