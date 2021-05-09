#include "Internal_Time.h"

#define _POSIX_C_SOURCE 199309L /* To get POSIX clock support */

#include <unistd.h>
#include <time.h>
#include <errno.h>

bool Clock_StartClock() {
  return true;
}

void Clock_SleepMilliseconds(long duration) {
  struct timespec ts;
  int res;

  ts.tv_sec = duration / 1000;
  ts.tv_nsec = (duration % 1000) * 1000000;

  do {
    res = nanosleep(&ts, &ts);
  } while (res && errno == EINTR);
}