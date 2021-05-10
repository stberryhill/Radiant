/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "Internal_Time.h"
#include <mach/mach_time.h>


static double clockScalar = 0;

bool Clock_StartClock()
{
	mach_timebase_info_data_t tb;

	if(mach_timebase_info(&tb) == KERN_SUCCESS && tb.denom != 0)
	{
		/* Since mach_absolute_time defaults to nanoseconds, we devide by one million to convert to milliseconds */
		clockScalar = (tb.numer / tb.denom) / 1000000.0;

		return true;
	}

	return false;	
}

double System_TimeMillis()
{
	return mach_absolute_time() * clockScalar;
}

/*
void i_sleepMilli(uint64 milli)
{
	//since usleep expects nanoseconds, multiply by 1000000
	usleep(milli * 1000);
}*/
