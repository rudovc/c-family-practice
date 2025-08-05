#include "maybe.h"

#include <stdio.h>
#include <stdlib.h>

#include "heaparray.h"

IMPLEMENT_UNWRAP(MaybeChar, char);
IMPLEMENT_NEW_NOTHING(MaybeChar);
IMPLEMENT_NEW_EXISTS(MaybeChar, char);

IMPLEMENT_UNWRAP(MaybeInt32, int32_t)
IMPLEMENT_NEW_NOTHING(MaybeInt32)
IMPLEMENT_NEW_EXISTS(MaybeInt32, int32_t)
