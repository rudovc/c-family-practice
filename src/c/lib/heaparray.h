#pragma once

#include <stddef.h>
#include <stdint.h>

#include "arena.h"
#include "str.h"

#define DECLARE_HEAP_ARRAY(T, N) \
  typedef struct \
  { \
    T* arr; \
    int32_t len; \
  } N; \
  N new_##N(int32_t len, T* start); \
  N reverse_##N(N* array, ArenaAllocator* allocator);

DECLARE_HEAP_ARRAY(int32_t, Int32Array)

#define IMPLEMENT_HEAP_ARRAY(T, N) \
  N new_##N(int32_t len, T* start) \
  { \
    N int_array = {.arr = start, .len = len}; \
    return int_array; \
  }

int32_t calculate_size_of_int32_array(int len);

DECLARE_HEAP_ARRAY(String, StringArray)
