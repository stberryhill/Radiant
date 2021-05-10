/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _RADIANT_INTERNAL_FILE_H
#define _RADIANT_INTERNAL_FILE_H

#include "RadiantFile.h"
#include <stdbool.h>

struct File {
  FILE *descriptor;
  int size;
  bool reachedEndOfFile;
};


#endif
