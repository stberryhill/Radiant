/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef INTERNAL_LOGGER_H
#define INTERNAL_LOGGER_H

#include <stdio.h>

struct Logger {
 FILE *filePtr;
 bool outputToTerminal;
};

#endif