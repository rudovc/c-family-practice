#include <stddef.h>

struct IntArray
{
  int* arr;
  int len;
};

typedef struct IntArray IntArray;

IntArray initialize_int_array(int len, void*(allocator)(size_t len));
IntArray reverse_int_array(IntArray* array, void*(allocator)(size_t len));
