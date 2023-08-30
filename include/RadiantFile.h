/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _RADIANT_FILE_H
#define _RADIANT_FILE_H

#include "RadiantAPIMacro.h"
#include <stdio.h>
#include <stdbool.h>

extern const int FILE_EOF;

typedef enum {
  FILE_MODE_READ,
  FILE_MODE_WRITE,
  FILE_MODE_READ_WRITE
} FileMode;

typedef struct File File;

RADIANT_API File *File_Open(const char *fileName, FileMode fileMode);
RADIANT_API void File_Close(File *file);
RADIANT_API void File_ReadLine(File *file, const int characterLimit, char *output);
RADIANT_API char File_ReadCharacter(File *file);
RADIANT_API char File_PeekCharacter(File *file);
RADIANT_API void File_Rewind(File *file, int numCharactersToRewind);
RADIANT_API long File_GetReadWritePosition(File *file);
RADIANT_API bool File_ReachedEndOfFile(File *file);
RADIANT_API void File_ReadEntireContentsToString(File *file, char *output);
RADIANT_API int File_GetSize(File *file);

#endif
