#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const size_t input_buffer_size = 13;

enum task {
  print_user_input,
  reverse_array,
  twod_array,
  dynamic_array,
  linked_list,
  doubly_linked_list
};

static const char *const options[] = {"print",   "reverse", "2d-array",
                                      "dynamic", "linked",  "doubly-linked"};

int main() {
  char buffer[input_buffer_size];

  char *status = fgets(buffer, (int)sizeof(buffer), stdin);
  char *input = malloc(input_buffer_size);

  int err = sscanf(buffer, "%s", input);

  if (err == EOF) {
    printf("Some error happened!");
  }

  if (strcmp(input, options[print_user_input]) == 0) {
    printf("%s\n", input);
  }

  return 1;
}
