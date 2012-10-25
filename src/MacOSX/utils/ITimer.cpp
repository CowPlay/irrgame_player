/*
 * ITimer.cpp
 *
 *  Created on: Oct 24, 2012
 *      Author: gregorytkach
 */

#include "utils/ITimer.h"
#include <time.h>
#include <sys/time.h>

namespace irrgame
{
	namespace utils
	{
		//! Returns current real time in milliseconds of the system.
		//! Platform dependent
		u32 ITimer::getRealTime()
		{
			timeval tv;
			gettimeofday(&tv, 0);
			return (u32) (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		}
	}
}

