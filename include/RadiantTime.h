/*
 * author: S. Tyler Berryhill
 * email: sean.tyler.berryhill@gmail.com
 */

#ifndef _RADIANT_TIMERS_H
#define _RADIANT_TIMERS_H

#include "RadiantAPIMacro.h"

typedef struct Timer Timer;

RADIANT_API double System_TimeNanos();
RADIANT_API double System_TimeMillis();
RADIANT_API double System_TimeSeconds();

#endif