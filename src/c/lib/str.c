#include "str.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "heaparray.h"

String new_string(int len, char *start) {
  String string = {.str = start, .len = len};

  return string;
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
    new_char_arr.str[(string->len - 1) - i] = string->str[i];
  }

  return new_char_arr;
}

String *split_string_on_char(String *string, ArenaAllocator *allocator,
                             char split_char) {}
