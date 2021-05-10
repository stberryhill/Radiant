/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "RadiantFile.h"
#include "Internal_File.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int FILE_EOF = EOF;
const static int MAX_STRING_SIZE = 4096;

File *File_Open(const char *fileName, int qf_file_mode) {
  File *file = malloc(sizeof *file);
  
  const int MAX_FOPEN_MODE_LENGTH = 3;
  char mode[MAX_FOPEN_MODE_LENGTH + 1]; /* +1 for null terminator */
  switch (qf_file_mode) {
    case FILE_MODE_READ:
      strcpy(mode, "r");
      break;
      
    case FILE_MODE_WRITE:
      strcpy(mode, "w");
      break;
      
    case FILE_MODE_READ_WRITE:
      strcpy(mode, "r+");
      break;
      
    default:
      printf("File error - unsupported file mode passed to qf_openFile.\n");
      exit(-1);
      break;
  }
  
  FILE *fp = fopen(fileName, mode);
  if (!fp) {
    printf("File error - %s could not be opened...\n", fileName);
    exit(-1);
  }
  
  fseek(fp, 0L, SEEK_END);
  const int size = ftell(fp);
  rewind(fp);
  
  file->descriptor = fp;
  file->size = size;
  file->reachedEndOfFile = false;
  
  return file;
}

void File_Close(File *file) {
  fclose(file->descriptor);
  free(file);
}

void File_ReadLine(File *file, const int characterLimit, char *output) {
  if (fgets(output, characterLimit, file->descriptor) == NULL) {
    file->reachedEndOfFile = true;
  }
}

char File_ReadCharacter(File *file) {
  char c;
  if ( (c = fgetc(file->descriptor)) == EOF) {
    file->reachedEndOfFile = true;
  }

  return c;
}

/*
 * Peek at the next character without advancing position in file
 */
char File_PeekCharacter(File *file) {
  char c;
  if ( (c = fgetc(file->descriptor)) != FILE_EOF) {
    fseek(file->descriptor, -1, SEEK_CUR);
  }
  return c;
}

void File_Rewind(File *file, int numCharactersToRewind) {
  fseek(file->descriptor, -numCharactersToRewind, SEEK_CUR);
}

long File_GetReadWritePosition(File *file) {
  return ftell(file->descriptor);
}

bool File_ReachedEndOfFile(File *file) {
  return file->reachedEndOfFile;
}

void File_ReadEntireContentsToString(File *file, char *output) {

  if (file->size > MAX_STRING_SIZE) {
    printf("File error - cannot read file contents to string, exceeds defined maximum string size %d.\n", MAX_STRING_SIZE);
    exit(-1);
  }
  const int bytesPerElement = 1;
  const int numElements = file->size;
  
  rewind(file->descriptor);                                       /* make sure we start at beginning */
  fread(output, bytesPerElement, numElements, file->descriptor);
  
  output[numElements] = '\0';                                     /* add a null terminator */
}

int File_GetSize(File *file) {
  return file->size;
}
