#pragma once

#include <stdint.h>

#include "intarray.h"

enum maybe
{
  nothing,
  exists
};

#define MAYBE(T) \
  typedef struct \
  { \
    enum maybe exists; \
    T item; \
  }

MAYBE(char) MaybeChar;
MAYBE(char*) MaybeString;

MAYBE(int32_t) MaybeInt32;
MAYBE(Int32Array) MaybeInt32Array;

#define UNWRAP_H(T, R) R unwrap_##T(T maybe_struct);

#define NEW_NOTHING_H(T) T new_nothing_##T();

#define NEW_EXISTS_H(T, R) T new_exists_##T(R item);

UNWRAP_H(MaybeChar, char);
UNWRAP_H(MaybeString, char*);

UNWRAP_H(MaybeInt32, int32_t)
UNWRAP_H(MaybeInt32Array, Int32Array)

NEW_NOTHING_H(MaybeChar);
NEW_NOTHING_H(MaybeString);

NEW_NOTHING_H(MaybeInt32)
NEW_NOTHING_H(MaybeInt32Array)

NEW_EXISTS_H(MaybeChar, char);
NEW_EXISTS_H(MaybeString, char*);

NEW_EXISTS_H(MaybeInt32, int32_t)
NEW_EXISTS_H(MaybeInt32Array, Int32Array)

#define UNWRAP(T, R) \
  R unwrap_##T(T maybe_struct) \
  { \
    if (maybe_struct.exists) { \
      return maybe_struct.item; \
    } \
    perror("Called 'unwrap' on empty Maybe<" #R ">"); \
    abort(); \
  }

#define NEW_NOTHING(T) \
  T new_nothing_##T() \
  { \
    return (T) {.exists = nothing}; \
  }

#define NEW_EXISTS(T, R) \
  T new_exists_##T(R item) \
  { \
    return (T) {.exists = nothing, .item = item}; \
  }
