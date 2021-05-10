/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "RadiantLogger.h"
#include "Internal_Logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

Logger *Logger_OpenFileLogger(const char *fileName, bool outputToTerminal) {
  Logger *logger = malloc(sizeof *logger);
  logger->filePtr = fopen(fileName, "w");

  if (!logger->filePtr) {
    printf("(%s:%d) [Error] Logger could not open file \"%s\" for logging.\n", __FILE__, __LINE__, fileName);
    exit(-1);
  }

  logger->outputToTerminal = outputToTerminal;

  return logger;
}

Logger *Logger_OpenConsoleLogger() {
  Logger *logger = malloc(sizeof *logger);
  logger->outputToTerminal = true;

  return logger;
}

void Logger_Info(const Logger *logger, const char *message, ...) {
  va_list variableArgumentList;
  va_start(variableArgumentList, message);
  
  if (logger->filePtr) {
    fprintf(logger->filePtr, "[Info] ");
    vfprintf(logger->filePtr, message, variableArgumentList);
    fprintf(logger->filePtr, "\n");
    fflush(logger->filePtr);
  }
  
  if (logger->outputToTerminal) {
    printf("[Info] ");
    printf(message, variableArgumentList);
    printf("\n");
  }

  va_end(variableArgumentList);
}

void Logger_Warn(const Logger *logger, const char *message, ...) {
  va_list variableArgumentList;
  va_start(variableArgumentList, message);
  
  if (logger->filePtr) {
    fprintf(logger->filePtr, "[Warning] ");
    vfprintf(logger->filePtr, message, variableArgumentList);
    fprintf(logger->filePtr, "\n");
    fflush(logger->filePtr);
  }

  if (logger->outputToTerminal) {
    printf("[Warning] ");
    printf(message, variableArgumentList);
    printf("\n");
  }

  va_end(variableArgumentList);
}

void Logger_Error(const Logger *logger, const char *message, ...) {
  va_list variableArgumentList;
  va_start(variableArgumentList, message);
  
  if (logger) {
    fprintf(logger->filePtr, "[Error] ");
    vfprintf(logger->filePtr, message, variableArgumentList);
    fprintf(logger->filePtr, "\n");
    fflush(logger->filePtr);
  }

  if (logger->outputToTerminal) {
    printf("[Error] ");
    printf(message, variableArgumentList);
    printf("\n");
  }

  va_end(variableArgumentList);
}

void Logger_Close(Logger *logger) {
  fclose(logger->filePtr);
  free(logger);
}
