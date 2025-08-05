#pragma once

#include <stdint.h>

#include "arena.h"
#include "maybe.h"

struct String {
        char* str;
        int32_t len;
};

typedef struct String String;

String new_string(int32_t len, char* start);

MAYBE(String) MaybeString;
DECLARE_UNWRAP(MaybeString, String);
DECLARE_NEW_NOTHING(MaybeString);
DECLARE_NEW_EXISTS(MaybeString, String);

MaybeString reverse_string(String* string, ArenaAllocator* allocator);
