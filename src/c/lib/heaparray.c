#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "arena.h"
#include "heaparray.h"
#include "str.h"

int static const SIZE_OF_INT32 = sizeof(int32_t);

int32_t calculate_size_of_int32_array(int32_t len) {
  return len * SIZE_OF_INT32;
}

IMPLEMENT_HEAP_ARRAY(int32_t, Int32Array)

Int32Array reverse_Int32Array(Int32Array *array, ArenaAllocator *allocator) {
  int32_t arr_size_in_bytes = calculate_size_of_int32_array(array->len);
  int32_t *start =
      allocate_to_arena(arr_size_in_bytes, allocator, DEFAULT_ALIGNMENT);

  Int32Array new_int_arr = new_Int32Array(array->len, start);

  if (start == NULL) {
    errno = ENOMEM;
    perror("Error:");

    free_arena(*allocator);
    abort();
  }

  for (int i = 0; i < array->len; ++i) {
    new_int_arr.arr[(array->len - 1) - i] = array->arr[i];
  }

  return new_int_arr;
}

IMPLEMENT_HEAP_ARRAY(String, StringArray)
