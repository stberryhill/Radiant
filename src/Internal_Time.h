#ifndef _INTERNAL_TIME_H
#define _INTERNAL_TIME_H

struct Timer {
  double timeout;
  double timeLeft;
  bool stopped;
};

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