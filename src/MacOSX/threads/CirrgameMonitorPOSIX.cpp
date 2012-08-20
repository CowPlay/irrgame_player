/*
 * CirrgameMonitorPOSIX.cpp
 *
 *  Created on: Aug 14, 2012
 *      Author: gregorytkach
 */

#include "CirrgameMonitorPOSIX.h"
namespace irrgame
{
	namespace threads
	{
		//! Default constructor
		CirrgameMonitorPOSIX::CirrgameMonitorPOSIX()
		{
			pthread_mutex_init(&Handle, 0);
		}

		//! Destructor
		CirrgameMonitorPOSIX::~CirrgameMonitorPOSIX()
		{
			pthread_mutex_destroy(&Handle);
		}

		//! Acquires a lock for an object. This action also marks the beginning of a critical section.
		//! No other thread can enter the critical section unless it is executing the instructions
		//! in the critical section using a different locked object.
		void CirrgameMonitorPOSIX::enter()
		{
			pthread_mutex_lock(&Handle);
		}

		//! Releases the lock on an object. This action also marks the end of a critical section protected by the locked object.
		void CirrgameMonitorPOSIX::exit()
		{
			pthread_mutex_unlock(&Handle);
		}

		//! irrgameMonitor creator. Internal function. Please do not use.
		irrgameMonitor* createIrrgameMonitor()
		{
			return new CirrgameMonitorPOSIX();
		}
	}
}

