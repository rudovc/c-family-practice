#pragma once

#include <stdint.h>

enum maybe {
        NOTHING,
        EXISTS
};

#define MAYBE(T) \
        typedef struct { \
                enum maybe exists; \
                T item; \
        }

#define DECLARE_UNWRAP(T, R) R unwrap_##T(T maybe_struct);

#define DECLARE_NEW_NOTHING(T) T new_nothing_##T();

#define DECLARE_NEW_EXISTS(T, R) T new_exists_##T(R item);

MAYBE(char) MaybeChar;
DECLARE_UNWRAP(MaybeChar, char);
DECLARE_NEW_NOTHING(MaybeChar);
DECLARE_NEW_EXISTS(MaybeChar, char);

MAYBE(int32_t) MaybeInt32;
DECLARE_UNWRAP(MaybeInt32, int32_t)
DECLARE_NEW_NOTHING(MaybeInt32)
DECLARE_NEW_EXISTS(MaybeInt32, int32_t)

#define IMPLEMENT_UNWRAP(T, R) \
        R unwrap_##T(T maybe_struct) \
        { \
                if (maybe_struct.exists) { \
                        return maybe_struct.item; \
                } \
                int32_t err = fprintf(stderr, "Called 'unwrap' on empty Maybe<" #R ">"); \
                if (err < 0) { \
                        perror("Error"); \
                } \
                abort(); \
        }

#define IMPLEMENT_NEW_NOTHING(T) \
        T new_nothing_##T() \
        { \
                return (T) {.exists = nothing}; \
        }

#define IMPLEMENT_NEW_EXISTS(T, R) \
        T new_exists_##T(R item) \
        { \
                return (T) {.exists = exists, .item = item}; \
        }
