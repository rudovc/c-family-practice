#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const size_t INPUT_BUFFER_SIZE = 13;

struct IntArray {
  int *arr;
  int len;
};

typedef struct IntArray IntArray;

IntArray initialize_int_array(int len) {
  IntArray int_array = {.arr = malloc(len), .len = len};

  return int_array;
}

IntArray reverse_int_array(IntArray *array) {
  IntArray new_int_arr = initialize_int_array(array->len);

  for (int i = 0; i < array->len; ++i) {
    new_int_arr.arr[(array->len - 1) - i] = array->arr[i];
  }

  return new_int_arr;
}

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
  char buffer[INPUT_BUFFER_SIZE];

  char *status = fgets(buffer, (int)sizeof(buffer), stdin);
  char *input = malloc(INPUT_BUFFER_SIZE);

  if (status == NULL) {
    printf("Some error happened!");

    free(status);
    free(input);

    return 0;
  }

  int err = sscanf(buffer, "%s", input);

  if (err == EOF) {
    printf("Some error happened!");
    free(input);

    return 0;
  }

  if (strcmp(input, OPTIONS[print_user_input_task]) == 0) {
    printf("%s\n", input);
  }

  if (strcmp(input, OPTIONS[reverse_array_task]) == 0) {
    IntArray input_int_array = initialize_int_array(4);

    int array_to_reverse[] = {1, 4, 3, 2};

    input_int_array.arr = array_to_reverse;

    IntArray output_int_array = reverse_int_array(&input_int_array);

    for (int i = 0; i < output_int_array.len; ++i) {
      printf("%d\n", output_int_array.arr[i]);
    }
  }

  free(input);

  return 0;
}
