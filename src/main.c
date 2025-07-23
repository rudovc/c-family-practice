#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t input_buffer_size = 10;

enum task
{
  print_user_input,
  reverse_array,
  twod_array,
  dynamic_array,
  linked_list,
  doubly_linked_list
};

int main()
{
  char buffer[input_buffer_size];

  char* status = fgets(buffer, sizeof(*buffer), stdin);

  char* input = malloc(input_buffer_size);
  int err = sscanf(buffer, "%s", input);

  if (err == EOF) {
    printf("Some error happened!");
  }

  printf("You typed in: %s", buffer);
  printf("You typed in: %s", input);

  return 1;
}
