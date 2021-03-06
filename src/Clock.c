/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "RadiantTime.h"
#include "Internal_Time.h"

#include <stdlib.h>
#include <stdio.h>

static double deltaT;
static double timeOfLastTick;
static long targetTimePerFrame;
static unsigned long tTickCount;

void Clock_Start() {
  if (!Clock_StartClock()) {
    printf("Error - tempus could not start a system clock.\n");
    exit(-1);
  }

  tTickCount = 0;
  timeOfLastTick = System_TimeMillis();
}

void Clock_Tick() {
  /* TODO make deltaT be 1 when fps = 60, > 1 when fps < 60, and < 1 when fps > 60? */
  tTickCount++;
  const double lastTick = timeOfLastTick;
  timeOfLastTick = System_TimeMillis();
  deltaT = (timeOfLastTick - lastTick) / 1000.0;

}

double Clock_DeltaT() {
  return deltaT;
}

double Clock_SecondsSinceLastTick() {
  return (System_TimeMillis() - timeOfLastTick) / 1000.0;
}

double Clock_MillisecondsSinceLastTick() {
  return System_TimeMillis() - timeOfLastTick;
}

unsigned long Clock_GetTickCount() {
  return tTickCount;
}

void Clock_timer_setTargetFps(int fps) {
  targetTimePerFrame = 1.0 / fps;
}

int Clock_Fps() {
  return (int) (1.0 / deltaT);
}
