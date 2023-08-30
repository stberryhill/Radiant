/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _INTERNAL_TIME_H
#define _INTERNAL_TIME_H

#include "RadiantTime.h"

#include <stdbool.h>

struct Timer {
  double timeout;
  double timeLeft;
  bool stopped;
};

/* Platform-dependent */
bool Clock_StartClock();
double System_TimeNanos();
double System_TimeMillis();
double System_TimeSeconds();

/* Platform independent */
void Clock_Start();
void Clock_Tick();
double Clock_SecondsSinceLastTick();
double Clock_MillisecondsSinceLastTick();
unsigned long Clock_GetTickCount();
double  Clock_DeltaT();
void Clock_SetTargetFps(int fps);
int Clock_Fps();
void Clock_SleepMilliseconds(long duration);

#endif
