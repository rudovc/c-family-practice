#include "maybe.h"

UNWRAP(MaybeChar, char);
UNWRAP(MaybeString, char *);

UNWRAP(MaybeInt32, int32_t)
UNWRAP(MaybeInt32Array, Int32Array)

NEW_NOTHING(MaybeChar);
NEW_NOTHING(MaybeString);

NEW_NOTHING(MaybeInt32)
NEW_NOTHING(MaybeInt32Array)

NEW_EXISTS(MaybeChar, char);
NEW_EXISTS(MaybeString, char *);

NEW_EXISTS(MaybeInt32, int32_t)
NEW_EXISTS(MaybeInt32Array, Int32Array)
