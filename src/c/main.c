#include <stdio.h>
#include <string.h>

#include "./lib/arena.h"
#include "./lib/intarray.h"

static const ptrdiff_t INPUT_BUFFER_SIZE = 13;
static const ptrdiff_t REVERSE_ARRAY_SIZE = 4 * sizeof(int32_t);

enum task {
  print_user_input_task,
  reverse_array_task,
  twod_array_task,
  dynamic_array_task,
  linked_list_task,
  doubly_linked_list_task
};

static const char *const OPTIONS[] = {"print",   "reverse", "2d-array",
                                      "dynamic", "linked",  "doubly-linked"};

int main() {
  ArenaAllocator arena =
      new_arena_allocator(INPUT_BUFFER_SIZE + (REVERSE_ARRAY_SIZE * 2));

  char buffer[INPUT_BUFFER_SIZE];

  char *status = fgets(buffer, (int)sizeof(buffer), stdin);
  char *input = allocate_to_arena(INPUT_BUFFER_SIZE, &arena, DEFAULT_ALIGNMENT);

  if (status == NULL || input == NULL) {
    perror("Some error happened!");

    free_arena(arena);

    return 1;
  }

  int err = sscanf(buffer, "%s", input);

  if (err == EOF || err < 0) {
    perror("Some error happened!");

    free_arena(arena);

    return 1;
  }

  if (strcmp(input, OPTIONS[print_user_input_task]) == 0) {
    printf("%s\n", input);
  }

  if (strcmp(input, OPTIONS[reverse_array_task]) == 0) {
    int *input_int_array_start = allocate_to_arena(
        calculate_size_of_int32_array(4), &arena, DEFAULT_ALIGNMENT);

    if (input_int_array_start == NULL) {
      perror("Failed to allocate memory!");

      free_arena(arena);

      return 1;
    }

    Int32Array input_int_array = new_int32_array(4, input_int_array_start);

    input_int_array.arr[0] = 1;
    input_int_array.arr[1] = 4;
    input_int_array.arr[2] = 3;
    input_int_array.arr[3] = 2;

    Int32Array output_int_array = reverse_int32_array(&input_int_array, &arena);

    for (int i = 0; i < output_int_array.len; ++i) {
      printf("%d\n", output_int_array.arr[i]);
    }
  }

  free_arena(arena);

  return 0;
}
