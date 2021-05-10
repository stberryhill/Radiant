/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _RADIANT_STRING_H
#define _RADIANT_STRING_H

#include "RadiantAPIMacro.h"
#include <stdbool.h>
#include <stdint.h>

RADIANT_API bool String_Equal(const char *a, const char *b);
RADIANT_API void String_Copy(const char *src, char *dest);
RADIANT_API void String_CopyN(const char *src, char *dest, uint32_t n);
RADIANT_API int String_Compare(const char *a, const char *b);
RADIANT_API int String_ToInt(char *number);

#endif