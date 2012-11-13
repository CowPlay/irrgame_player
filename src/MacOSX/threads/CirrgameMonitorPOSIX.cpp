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
#ifdef DEBUG
			setDebugName("CirrgameMonitorPOSIX");
#endif
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
			grab();
			pthread_mutex_lock(&Handle);
		}

		//! Releases the lock on an object. This action also marks the end of a critical section protected by the locked object.
		void CirrgameMonitorPOSIX::exit()
		{
			drop();
			pthread_mutex_unlock(&Handle);
		}

		//! irrgameMonitor creator. Internal function. Please do not use.
		irrgameMonitor* createIrrgameMonitor()
		{
			return new CirrgameMonitorPOSIX();
		}
	}
}

