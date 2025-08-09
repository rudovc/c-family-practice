#include "arena.h"

#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "maybe.h"

static const ptrdiff_t ERROR_BUFFER_SIZE = 64;

// TODO: This is not a sound implementation at all. If the memory gets copied elsewhere, all
// pointers already handed out are invalidated
void* try_grow_arena_by(ptrdiff_t size_in_bytes, ArenaAllocator* arena)
{
        free_arena(*arena);
        print_error("try_grow_arena_by not yet properly implemented");
        ptrdiff_t tail_offset = arena->tail - arena->head;
        size_t new_size = arena->size;

        if (size_in_bytes < 2 * arena->size) {
                new_size = arena->size * 2;
        } else {
                new_size = arena->size + size_in_bytes;
        }

        void* new_head = realloc(arena->head, new_size);

        if (new_head == NULL) {
                errno = ENOMEM;

                perror("Error:");

                return NULL;
        }

        void* new_tail = new_head + tail_offset;

        arena->head = new_head;
        arena->tail = new_tail;

        return new_tail;
}

// TODO: Bump downwards, not upwards
void* inner_allocate_to_arena(ptrdiff_t size_in_bytes, ArenaAllocator* arena, ptrdiff_t alignment)
{
        void* start = arena->tail;
        void* new_tail = start + size_in_bytes;

        uintptr_t remainder = (uintptr_t)new_tail % alignment;

        if (remainder != 0 && alignment > 0) {
                new_tail = new_tail + (alignment - remainder);
        } else {
                remainder = 0;
        }

        if (alignment < 0) {
                print_error("Provided negative alignment to function `allocate_to_arena`");

                return NULL;
        }

        if (new_tail > arena->head + arena->size) {
                ptrdiff_t difference = new_tail - (arena->head + arena->size);

                char buffer[ERROR_BUFFER_SIZE];
                int err = sprintf(buffer, "Missing %td  bytes for allocation", difference);

                if (err < 0) {
                        perror("Error:");
                }

                errno = ENOMEM;
                perror(buffer);

                return NULL;
        }

        arena->tail = new_tail;

        return start;
}

void* allocate_to_arena(ptrdiff_t size_in_bytes, ArenaAllocator* arena, ptrdiff_t alignment)
{
        void* start = inner_allocate_to_arena(size_in_bytes, arena, alignment);

        if (start == NULL) {
                // TODO: We'll revisit this later
                start = try_grow_arena_by(size_in_bytes, arena);

                if (start == NULL) {
                        abort();
                }

                return start;

                abort();
        }

        return start;
}

// Invalidates old references
void* reallocate_in_arena(void* object,
                          ptrdiff_t old_size_in_bytes,
                          ptrdiff_t new_size_in_bytes,
                          ArenaAllocator* arena,
                          ptrdiff_t alignment)
{
        void* new_start = allocate_to_arena(new_size_in_bytes, arena, alignment);

        memcpy(new_start, object, old_size_in_bytes);

        return new_start;
}

MaybePointer try_allocate_to_arena(ptrdiff_t size_in_bytes,
                                   ArenaAllocator* arena,
                                   ptrdiff_t alignment)
{
        void* start = inner_allocate_to_arena(size_in_bytes, arena, alignment);

        if (start == NULL) {
                // TODO: We'll revisit this later
                // start = try_grow_arena_by(size_in_bytes, arena);
                //
                // if (start == NULL) {
                //         return new_nothing_MaybePointer();
                // }

                return new_nothing_MaybePointer();
        }

        return new_exists_MaybePointer(start);
}

void free_arena(ArenaAllocator arena)
{
        return free(arena.head);
}

IMPLEMENT_UNWRAP(MaybeArenaAllocator, ArenaAllocator)
IMPLEMENT_NEW_NOTHING(MaybeArenaAllocator)
IMPLEMENT_NEW_EXISTS(MaybeArenaAllocator, ArenaAllocator)

IMPLEMENT_UNWRAP(MaybePointer, void*)
IMPLEMENT_NEW_NOTHING(MaybePointer)
IMPLEMENT_NEW_EXISTS(MaybePointer, void*)

ArenaAllocator inner_new_arena_allocator(ptrdiff_t size_in_bytes)
{
        void* head = malloc(size_in_bytes);

        ArenaAllocator arena = {.size = size_in_bytes, .head = head, .tail = head};

        if (head == NULL) {
                errno = ENOMEM;

                perror("Error:");
        }

        return arena;
}

ArenaAllocator new_arena_allocator(ptrdiff_t size_in_bytes)
{
        ArenaAllocator arena = inner_new_arena_allocator(size_in_bytes);

        if (arena.head == NULL) {
                abort();
        }

        return arena;
}

MaybeArenaAllocator try_new_arena_allocator(ptrdiff_t size_in_bytes)
{
        ArenaAllocator arena = inner_new_arena_allocator(size_in_bytes);

        if (arena.head == NULL) {
                return new_nothing_MaybeArenaAllocator();
        }

        return new_exists_MaybeArenaAllocator(arena);
}
