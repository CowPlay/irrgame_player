/*
 * CirrgameThreadPOSIX.h
 *
 *  Created on: Aug 13, 2012
 *      Author: gregorytkach
 */

#ifndef CIRRGAMETHREADPOSIX_H_
#define CIRRGAMETHREADPOSIX_H_

#include "threads/irrgameThread.h"
#include "pthread.h"
#include "core/collections/irrstring.h"

namespace irrgame
{
	namespace threads
	{
		extern "C" typedef void *(*pthread_callback)(void *);

		class CirrgameThreadPOSIX: public irrgameThread
		{
			public:

				//! Default constructor
				//! Platform dependent
				//@ param1 - thread name
				//@ param2 - input parameter
				CirrgameThreadPOSIX(delegateThreadCallback* callback,
						void* callbackArg = NULL, EThreadPriority prior =
								ETP_NORMAL, core::stringc name = "");

				//! Destructor
				virtual ~CirrgameThreadPOSIX();

				//! Causes the operating system to start thread, and optionally supplies an object containing data to be used by the method the thread executes
				//! Platform dependent
				virtual void start();

				//! Blocks the calling thread until a thread terminates.
				//! Platform dependent
				virtual void join();

				//! Causes the operating system to kill thread
				//! Platform dependent
//				virtual void kill();

			protected:
				//! Use for simply run func in individual thread
				static void ProceedFunc(irrgameThread* who);

			private:
				//! Thread priority
				EThreadPriority Priority;
				//! Thread HANDLE
				pthread_t Handle;
				//! Thread init attributes
				pthread_attr_t Attributes;
		};

	}
}

#endif /* CIRRGAMETHREADPOSIX_H_ */
