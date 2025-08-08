#pragma once

#include <stdint.h>

#include "arena.h"
#include "heaparray.h"
#include "maybe.h"

struct String {
        int32_t len;
        char* str;
};

typedef struct String String;

String copy_string(String* string, ArenaAllocator* allocator);

MAYBE(String) MaybeString;
DECLARE_UNWRAP(MaybeString, String);
DECLARE_NEW_NOTHING(MaybeString);
DECLARE_NEW_EXISTS(MaybeString, String);

DECLARE_HEAP_ARRAY(String, StringArray)
MAYBE(StringArray) MaybeStringArray;
DECLARE_UNWRAP(MaybeStringArray, StringArray);
DECLARE_NEW_NOTHING(MaybeStringArray);
DECLARE_NEW_EXISTS(MaybeStringArray, StringArray);

MAYBE(MaybeStringArray*) MaybeStringArrayPointer;
DECLARE_UNWRAP(MaybeStringArrayPointer, MaybeStringArray*);
DECLARE_NEW_NOTHING(MaybeStringArrayPointer);
DECLARE_NEW_EXISTS(MaybeStringArrayPointer, MaybeStringArray*);

MaybeString new_empty_string(int32_t len, ArenaAllocator* allocator);
MaybeString new_string_from_bytes(int32_t len, ArenaAllocator* allocator, const char* contents);
MaybeString reverse_string(String* string, ArenaAllocator* allocator);
MaybeStringArray split_string_on_char(String* string, ArenaAllocator* allocator, char delimiter);

char* new_cstring_from_string(String* string, ArenaAllocator* allocator);

void print_string(String* string);
void println_string(String* string);
