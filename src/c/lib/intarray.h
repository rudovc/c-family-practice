#include <stddef.h>
#include <stdint.h>

#ifndef ARENA
#  include "arena.h"
#  define ARENA
#endif

struct Int32Array
{
  int32_t* arr;
  int32_t len;
};

typedef struct Int32Array Int32Array;

Int32Array new_int32_array(int32_t len, int32_t* start);
Int32Array reverse_int32_array(Int32Array* array, ArenaAllocator* allocator);
int32_t calculate_size_of_int32_array(int len);
