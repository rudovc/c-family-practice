#pragma once

#include <stdint.h>

#include "heaparray.h"
#include "str.h"

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
MAYBE(String) MaybeString;

MAYBE(int32_t) MaybeInt32;
MAYBE(Int32Array) MaybeInt32Array;

#define DECLARE_UNWRAP(T, R) R unwrap_##T(T maybe_struct);

#define DECLARE_NEW_NOTHING(T) T new_nothing_##T();

#define DECLARE_NEW_EXISTS(T, R) T new_exists_##T(R item);

DECLARE_UNWRAP(MaybeChar, char);
DECLARE_UNWRAP(MaybeString, String);

DECLARE_UNWRAP(MaybeInt32, int32_t)
DECLARE_UNWRAP(MaybeInt32Array, Int32Array)

DECLARE_NEW_NOTHING(MaybeChar);
DECLARE_NEW_NOTHING(MaybeString);

DECLARE_NEW_NOTHING(MaybeInt32)
DECLARE_NEW_NOTHING(MaybeInt32Array)

DECLARE_NEW_EXISTS(MaybeChar, char);
DECLARE_NEW_EXISTS(MaybeString, String);

DECLARE_NEW_EXISTS(MaybeInt32, int32_t)
DECLARE_NEW_EXISTS(MaybeInt32Array, Int32Array)

#define IMPLEMENT_UNWRAP(T, R) \
  R unwrap_##T(T maybe_struct) \
  { \
    if (maybe_struct.exists) { \
      return maybe_struct.item; \
    } \
    fprintf(stderr, "Called 'unwrap' on empty Maybe<" #R ">"); \
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
