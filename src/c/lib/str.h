#pragma once

#include <stdint.h>

#include "arena.h"

struct String
{
  char* str;
  int32_t len;
};

typedef struct String String;

String new_string(int32_t len, char* start);

String reverse_string(String* string, ArenaAllocator* allocator);
