/*
 * CirrgameMonitorPOSIX.h
 *
 *  Created on: Aug 14, 2012
 *      Author: gregorytkach
 */

#ifndef CIRRGAMEMONITORPOSIX_H_
#define CIRRGAMEMONITORPOSIX_H_

#include "threads/irrgameMonitor.h"
#include "pthread.h"

namespace irrgame
{
	namespace threads
	{
		class CirrgameMonitorPOSIX: public irrgameMonitor
		{
			public:

				//! Default constructor
				CirrgameMonitorPOSIX();

				//! Destructor
				virtual ~CirrgameMonitorPOSIX();

				//! Acquires a lock for an object. This action also marks the beginning of a critical section.
				//! No other thread can enter the critical section unless it is executing the instructions
				//! in the critical section using a different locked object.
				virtual void enter();

				//! Releases the lock on an object. This action also marks the end of a critical section protected by the locked object.
				virtual void exit();

			private:
				//! POSIX mutex realization
				pthread_mutex_t Handle;
		};
	}
}

#endif /* CIRRGAMEMONITORPOSIX_H_ */
