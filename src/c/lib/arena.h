#pragma once

#include <stddef.h>
#include <stdint.h>

#include "maybe.h"

struct ArenaAllocator {
        size_t size;
        void* head;
        void* tail;
};

typedef struct ArenaAllocator ArenaAllocator;

ptrdiff_t const DEFAULT_ALIGNMENT = 8;

MAYBE(ArenaAllocator) MaybeArenaAllocator;
DECLARE_UNWRAP(MaybeArenaAllocator, ArenaAllocator);
DECLARE_NEW_NOTHING(MaybeArenaAllocator);
DECLARE_NEW_EXISTS(MaybeArenaAllocator, ArenaAllocator);

MAYBE(void*) MaybePointer;
DECLARE_UNWRAP(MaybePointer, void*);
DECLARE_NEW_NOTHING(MaybePointer);
DECLARE_NEW_EXISTS(MaybePointer, void*);

void* allocate_to_arena(ptrdiff_t size_in_bytes, ArenaAllocator* arena, ptrdiff_t alignment);
MaybePointer try_allocate_to_arena(ptrdiff_t size_in_bytes,
                                   ArenaAllocator* arena,
                                   ptrdiff_t alignment);
void* try_grow_arena_by(ptrdiff_t size_in_bytes, ArenaAllocator* arena);
void free_arena(ArenaAllocator arena);
ArenaAllocator new_arena_allocator(ptrdiff_t size_in_bytes);
MaybeArenaAllocator try_new_arena_allocator(ptrdiff_t size_in_bytes);
