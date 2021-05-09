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
  timeOfLastTick = Clock_TimeMilliseconds();
}

void Clock_Tick() {
  /* TODO make deltaT be 1 when fps = 60, > 1 when fps < 60, and < 1 when fps > 60? */
  tTickCount++;
  const double lastTick = timeOfLastTick;
  timeOfLastTick = Clock_TimeMilliseconds();
  deltaT = (timeOfLastTick - lastTick) / 1000.0;

}

double Clock_DeltaT() {
  return deltaT;
}

double Clock_SecondsSinceLastTick() {
  return (Clock_TimeMilliseconds() - timeOfLastTick) / 1000.0;
}

double Clock_MillisecondsSinceLastTick() {
  return Clock_TimeMilliseconds() - timeOfLastTick;
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
