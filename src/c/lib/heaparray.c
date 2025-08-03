#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "arena.h"
#include "heaparray.h"

int static const SIZE_OF_INT32 = sizeof(int32_t);

int32_t calculate_size_of_int32_array(int len) { return len * SIZE_OF_INT32; }

Int32Array new_int32_array(int len, int *start) {
  Int32Array int_array = {.arr = start, .len = len};

  return int_array;
}

String new_string(int len, char *start) {
  String string = {.arr = start, .len = len};

  return string;
}

Int32Array reverse_int32_array(Int32Array *array, ArenaAllocator *allocator) {
  int arr_size_in_bytes = calculate_size_of_int32_array(array->len);
  int *start =
      allocate_to_arena(arr_size_in_bytes, allocator, DEFAULT_ALIGNMENT);

  Int32Array new_int_arr = new_int32_array(array->len, start);

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

String reverse_string(String *string, ArenaAllocator *allocator) {
  int arr_size_in_bytes = calculate_size_of_int32_array(string->len);
  char *start =
      allocate_to_arena(arr_size_in_bytes, allocator, DEFAULT_ALIGNMENT);

  String new_char_arr = new_string(string->len, start);

  if (start == NULL) {
    errno = ENOMEM;
    perror("Error:");

    free_arena(*allocator);
    abort();
  }

  for (int i = 0; i < string->len; ++i) {
    new_char_arr.arr[(string->len - 1) - i] = string->arr[i];
  }

  return new_char_arr;
}
