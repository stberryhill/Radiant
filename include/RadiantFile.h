/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _RADIANT_FILE_H
#define _RADIANT_FILE_H

#include <stdio.h>
#include <stdbool.h>

extern const int FILE_EOF;

enum FileMode {
  FILE_MODE_READ,
  FILE_MODE_WRITE,
  FILE_MODE_READ_WRITE
};

typedef struct File File;

File *File_Open(const char *fileName, int qf_file_mode);
void File_Close(File *file);
void File_ReadLine(File *file, const int characterLimit, char *output);
char File_ReadCharacter(File *file);
char File_PeekCharacter(File *file);
void File_Rewind(File *file, int numCharactersToRewind);
long File_GetReadWritePosition(File *file);
bool File_ReachedEndOfFile(File *file);
void File_ReadEntireContentsToString(File *file, char *output);
int File_GetSize(File *file);

#endif
