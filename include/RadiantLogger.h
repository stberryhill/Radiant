#ifndef _RADIANT_LOGGER_H
#define _RADIANT_LOGGER_H

#include "RadiantAPIMacro.h"
#include <stdbool.h>

typedef struct Logger Logger;

RADIANT_API Logger *Logger_OpenFileLogger(const char *fileName, bool outputToTerminal);
RADIANT_API Logger *Logger_OpenConsoleLogger();
RADIANT_API void Logger_Info(const Logger *logger, const char *message, ...);
RADIANT_API void Logger_Warn(const Logger *logger, const char *message, ...);
RADIANT_API void Logger_Error(const Logger *logger, const char *message, ...);
RADIANT_API void Logger_Close(Logger *logger);

#endif
