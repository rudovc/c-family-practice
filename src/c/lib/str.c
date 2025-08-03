#include "str.h"
#include "error.h"
#include "heaparray.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

String new_string(int len, char *start) {
  String string = {.str = start, .len = len};

  return string;
}

IMPLEMENT_UNWRAP(MaybeString, String);
IMPLEMENT_NEW_NOTHING(MaybeString);
IMPLEMENT_NEW_EXISTS(MaybeString, String);

MaybeString reverse_string(String *string, ArenaAllocator *allocator) {
  int arr_size_in_bytes = calculate_size_of_int32_array(string->len);
  char *start =
      allocate_to_arena(arr_size_in_bytes, allocator, DEFAULT_ALIGNMENT);

  String new_char_arr = new_string(string->len, start);

  if (start == NULL) {
    errno = ENOMEM;
    perror("Error:");

    return new_nothing_MaybeString();
  }

  for (int i = 0; i < string->len; ++i) {
    new_char_arr.str[(string->len - 1) - i] = string->str[i];
  }

  return new_exists_MaybeString(new_char_arr);
}

// MaybeStringArray split_string_on_char(String *string, ArenaAllocator
// *allocator,
//                                       char delimiter) {
//   size_t size_of_string_in_bytes = string->len * sizeof(char);
//
//   if (size_of_string_in_bytes > PTRDIFF_MAX) {
//     print_error("Tried to perform split operation on string that's too
//     long");
//
//     return new_nothing_MaybeStringArray();
//   }
//
//   char str_char = 0;
//   int buffer_i = 0;
//   char *buffer =
//       allocate_to_arena(size_of_string_in_bytes, allocator,
//       DEFAULT_ALIGNMENT);
//   MaybeStringArray string_array = new_nothing_MaybeStringArray();
//
//   for (int i = 0; i < string->len; i++) {
//     str_char = string->str[i];
//
//     if (str_char == delimiter) {
//       buffer_i = 0;
//
//       if (string_array.exists) {
//         // string_array.item.len =
//       }
//     } else {
//       buffer[buffer_i] = str_char;
//     }
//   }
// }
