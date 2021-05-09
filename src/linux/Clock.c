#include "RadiantTime.h"
#include "Internal_Time.h"

#define _POSIX_C_SOURCE 199309L /* To get POSIX clock support */

#include <unistd.h>
#include <time.h>
#include <errno.h>

static struct timespec ts;

bool Clock_StartClock() {
  return true;
}

/* TODO: Implement */
void Clock_SleepMilliseconds(long duration) {
/*   int res;

  ts.tv_sec = duration / 1000;
  ts.tv_nsec = (duration % 1000) * 1000000;

  do {
    res = nanosleep(&ts, &ts);
  } while (res && errno == EINTR); */
}

double System_TimeNanos() {
  clock_gettime(CLOCK_REALTIME, &ts);
  const double nanos = ts.tv_nsec; /* Convert nanos to millis */

  return nanos;
}

double System_TimeMillis() {
  clock_gettime(CLOCK_REALTIME, &ts);
  const double millis = ts.tv_nsec / 1000000; /* Convert nanos to millis */

  return millis;
}

double System_TimeSeconds() {
  clock_gettime(CLOCK_REALTIME, &ts);
  const double seconds = ts.tv_nsec / 1000000000; /* Convert nanos to millis */

  return seconds;
}