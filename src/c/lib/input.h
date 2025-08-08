#pragma once

#include <stddef.h>
#include <stdint.h>

#include "arena.h"
#include "str.h"

MaybeString take_user_input_stdin(int32_t buffer_size_in_bytes, ArenaAllocator* allocator);
