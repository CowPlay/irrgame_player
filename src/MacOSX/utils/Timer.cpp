/*
 * Timer.cpp
 *
 *  Created on: Aug 1, 2012
 *      Author: gregorytkach
 */

#include "./utils/Timer.h"
#include <time.h>
#include <sys/time.h>
namespace irrgame
{
	namespace utils
	{
		//! returns the current time in milliseconds
		void Timer::initTimer()
		{
			initVirtualTimer();
		}

		//! initializes the real timer
		u32 Timer::getRealTime()
		{
			timeval tv;
			gettimeofday(&tv, 0);
			return (u32) (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		}
	}
}

