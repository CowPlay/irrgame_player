/*
 * CirrgameThread.cpp
 *
 *  Created on: Aug 13, 2012
 *      Author: gregorytkach
 */

#include "CirrgameThreadPOSIX.h"
#include <sys/syscall.h>
#include <sys/types.h>
#include "pthread.h"
#include "signal.h"
#include "sched.h"
namespace irrgame
{
	namespace threads
	{
		//! Causes the operating system to sleep current thread.
		//! Platform dependies
		//@ param0 - time in msec.
		void irrgameThread::sleep(s32 time)
		{
			usleep(time);
		}

		//! Returns current thread id
		s32 irrgameThread::getCurrentThreadID()
		{
			return syscall(SYS_gettid);
		}

		//! Use for simply run func in each platform
		void CirrgameThreadPOSIX::ProceedFunc(irrgameThread* who)
		{
			//make thread sensitive for pthread_cancel()
			int prevCancelType;
			pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &prevCancelType);

			(*(who->getCallback()))(who->getCallbackArg());
		}

		//! Default constructor
		//! Platform dependies
		//@ param1 - thread name
		//@ param2 - input parameter
		CirrgameThreadPOSIX::CirrgameThreadPOSIX(
				delegateThreadCallback* callback, void* callbackArg,
				EThreadPriority prior, stringc name) :
				Priority(prior), Handle(0)
		{
			Callback = callback;
			CallbackArg = callbackArg;
			Name = name;
		}

		//! Destructor
		CirrgameThreadPOSIX::~CirrgameThreadPOSIX()
		{
			if (Handle)
				pthread_cancel(Handle);
		}

		//! Causes the operating system to start thread, and optionally supplies an object containing data to be used by the method the thread executes
		//! Platform dependies
		void CirrgameThreadPOSIX::start()
		{
			s32 error = 0;

			sched_param param;
			s32 policy = SCHED_FIFO;

//			pthread_attr_t attr;
			// init attr
//			error = pthread_attr_init(&attr);
//			IRR_ASSERT(error == 0);

//			error = pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
//			IRR_ASSERT(error == 0);

//			error = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
//			IRR_ASSERT(error == 0);

//			error = pthread_attr_setschedpolicy(&attr, policy);
//			IRR_ASSERT(error == 0);

			error = pthread_create(&Handle, 0,
					reinterpret_cast<pthread_callback>(ProceedFunc), this);
			IRR_ASSERT(error == 0);

//			error = pthread_attr_destroy(&attr);
//			IRR_ASSERT(error == 0);

			//init param
			error = pthread_getschedparam(Handle, &policy, &param);
			IRR_ASSERT(error == 0);

			s32 minPrio = sched_get_priority_min(SCHED_FIFO);
			s32 maxPrio = sched_get_priority_max(SCHED_FIFO);
			s32 deltaPrio = maxPrio - minPrio;

			switch (Priority)
			{
				case ETP_LOW:
				{
					param.sched_priority = minPrio + deltaPrio * 0.2;
					break;
				}

				case ETP_NORMAL:
				{
					param.sched_priority = minPrio + deltaPrio / 2;
					break;
				}
				case ETP_HIGH:
				{
					param.sched_priority = maxPrio - deltaPrio * 0.2;
					break;
				}
			}

			error = pthread_setschedparam(Handle, policy, &param);
			IRR_ASSERT(error == 0);

//			//check param
//			error = pthread_getschedparam(Handle, &policy, &param);
//			IRR_ASSERT(error == 0);
		}

		//! Blocks the calling thread until a thread terminates.
		//! Platform dependies
		void CirrgameThreadPOSIX::join()
		{
			pthread_join(Handle, 0);
		}

		//! Causes the operating system to kill thread
		//! Platform dependies
//		void CirrgameThreadPOSIX::kill()
//		{
//
//		}

		//! irrgameThread creator. Internal function. Please do not use.
		irrgameThread* createIrrgameThread(delegateThreadCallback* callback,
				void* callbackArg, EThreadPriority prior, stringc name)
		{
			return new CirrgameThreadPOSIX(callback, callbackArg, prior, name);
		}

	/*
	 * #include <cstdlib>
	 #include <iostream>
	 #include <memory>

	 #include <pthread.h>

	 class Thread
	 {
	 private:
	 pthread_t thread;

	 Thread(const Thread& copy);         // copy constructor denied
	 static void *thread_func(void *d)   { ((Thread *)d)->run(); }

	 public:
	 Thread()             {}
	 virtual ~Thread()    {}

	 virtual void run() = 0;

	 int start()          { return pthread_create(&thread, NULL,
	 Thread::thread_func, (void*)this); }
	 int wait ()          { return pthread_join  (thread, NULL); }
	 };

	 typedef std::auto_ptr<Thread> ThreadPtr;

	 int main(void)
	 {
	 class Thread_a:public Thread
	 {
	 public:
	 void run()
	 {
	 for (int i=0; i<20; i++, sleep(1))
	 std::cout << "a  " << std::endl;
	 }
	 };

	 class Thread_b:public Thread
	 {
	 public:
	 void run()
	 {
	 for(int i=0; i<20; i++, sleep(1))
	 std::cout << "  b" << std::endl;
	 }
	 };

	 ThreadPtr a( new Thread_a() );
	 ThreadPtr b( new Thread_b() );

	 if (a->start() != 0 || b->start() != 0)
	 return EXIT_FAILURE;

	 if (a->wait() != 0 || b->wait() != 0)
	 return EXIT_FAILURE;

	 return EXIT_SUCCESS;
	 } *
	 */

	}
}

