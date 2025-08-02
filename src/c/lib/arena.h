#include <stddef.h>
#include <stdint.h>

struct ArenaAllocator
{
  size_t size;
  void* head;
  void* tail;
};

typedef struct ArenaAllocator ArenaAllocator;
ptrdiff_t const DEFAULT_ALIGNMENT;

void* allocate_to_arena(ptrdiff_t size_in_bytes,
                        ArenaAllocator* arena,
                        ptrdiff_t alignment);
void free_arena(ArenaAllocator arena);
ArenaAllocator new_arena_allocator(ptrdiff_t size_in_bytes);
