#include "maybe.h"
#include "heaparray.h"
#include <stdio.h>
#include <stdlib.h>

IMPLEMENT_UNWRAP(MaybeChar, char);
IMPLEMENT_NEW_NOTHING(MaybeChar);
IMPLEMENT_NEW_EXISTS(MaybeChar, char);

IMPLEMENT_UNWRAP(MaybeInt32, int32_t)
IMPLEMENT_NEW_NOTHING(MaybeInt32)
IMPLEMENT_NEW_EXISTS(MaybeInt32, int32_t)

IMPLEMENT_UNWRAP(MaybeStringArray, StringArray)
IMPLEMENT_NEW_NOTHING(MaybeStringArray)
IMPLEMENT_NEW_EXISTS(MaybeStringArray, StringArray)

IMPLEMENT_UNWRAP(MaybeString, String);
IMPLEMENT_NEW_NOTHING(MaybeString);
IMPLEMENT_NEW_EXISTS(MaybeString, String);
