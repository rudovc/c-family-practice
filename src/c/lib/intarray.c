#include <stddef.h>

#ifndef INT_ARRAY
#include "intarray.h"
#define INT_ARRAY
#endif

IntArray initialize_int_array(int len, void *(allocator)(size_t len)) {
  IntArray int_array = {.arr = allocator(len), .len = len};

  return int_array;
}

IntArray reverse_int_array(IntArray *array, void *(allocator)(size_t len)) {
  IntArray new_int_arr = initialize_int_array(array->len, allocator);

  for (int i = 0; i < array->len; ++i) {
    new_int_arr.arr[(array->len - 1) - i] = array->arr[i];
  }

  return new_int_arr;
}
