#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma once
#include "arena.h"

static const ptrdiff_t ERROR_BUFFER_SIZE = 64;
ptrdiff_t const DEFAULT_ALIGNMENT = 8;

void *allocate_to_arena(ptrdiff_t size_in_bytes, ArenaAllocator *arena,
                        ptrdiff_t alignment) {
  void *start = arena->tail;
  void *new_tail = start + size_in_bytes;

  uintptr_t remainder = (uintptr_t)new_tail % alignment;

  if (remainder != 0) {
    new_tail = new_tail + (alignment - remainder);
  }

  if (new_tail > arena->head + arena->size) {
    ptrdiff_t difference = new_tail - (arena->head + arena->size);

    char buffer[ERROR_BUFFER_SIZE];
    int err = sprintf(buffer, "Missing %td  bytes for allocation!", difference);

    if (err < 0) {
      perror("Missing room for allocation!");
    }

    perror(buffer);

    return NULL;
  }

  arena->tail = new_tail;

  return start;
}

void free_arena(ArenaAllocator arena) { return free(arena.head); }

ArenaAllocator new_arena_allocator(ptrdiff_t size_in_bytes) {
  void *head = malloc(size_in_bytes);

  ArenaAllocator arena = {.size = size_in_bytes, .head = head, .tail = head};

  return arena;
}
