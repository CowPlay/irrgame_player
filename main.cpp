/*
 * main.cpp
 *
 *  Created on: Jul 24, 2012
 *      Author: gregorytkach
 */
#include "irrgame.h"
#include "stub/io/CFileSystem.h"
using namespace irrgame;

using namespace io;
using namespace threads;

//#include "irrgamePlayer.h"

#include <stdio.h>
#include <dlfcn.h>
//#include "ctest.h"

//int main(int argc, char **argv)
//{
//   void *lib_handle;
//   double (*fn)(int *);
//   int x;
//   char *error;
//
//   lib_handle = dlopen("/opt/lib/libctest.so", RTLD_LAZY);
//   if (!lib_handle)
//   {
//      fprintf(stderr, "%s\n", dlerror());
//   }
//
//   fn = dlsym(lib_handle, "ctest1");
//   if ((error = dlerror()) != NULL)
//   {
//      fprintf(stderr, "%s\n", error);
//      exit(1);
//   }
//
//      exit(1);
//   (*fn)(&x);
//   printf("Valx=%d\n",x);
//
//   dlclose(lib_handle);
//   return 0;
//}
#include "pthread.h"
class C1
{
	public:
		int func1(void* arg)
		{
//			sched_param param;
//			sched_get_priority_max( )
//			sched_set
//			sched_setscheduler(irrgameThread::getCurrentThreadID(),);
//			()
			while (true)
				printf("1\n");

			return 0;
		}

		int func2(void* arg)
		{
			while (true)
				printf("2\n");

			return 0;
		}

		int func3(void* arg)
		{
			while (true)
				printf("3\n");

			return 0;
		}
};


//int main()
//{
//
////	int max = -777;
////	max = sched_get_priority_max(SCHED_OTHER);
//
////	int min = -777;
////	min = sched_get_priority_min(SCHED_OTHER);
//
//	C1* instance = new C1;
//
//	delegateThreadCallback* del1 = new delegateThreadCallback;
//	*del1 += NewDelegate(instance, &C1::func1);
//	irrgameThread* th1 = createIrrgameThread(del1, 0, ETP_LOW);
//	th1->start();
//
//	delegateThreadCallback* del2 = new delegateThreadCallback;
//	*del2 += NewDelegate(instance, &C1::func2);
//	irrgameThread* th2 = createIrrgameThread(del2, 0, ETP_NORMAL);
//	th2->start();
//
////	delegateThreadCallback* del3 = new delegateThreadCallback;
////	*del3 += NewDelegate(instance, &C1::func3);
////	irrgameThread* th3 = createIrrgameThread(del3, 0, ETP_HIGH);
////	th3->start();
//
////	fs->getWorkingDirectory();
//
////	IReadFile* file = IFileSystem::createReadFile("README.md");
////	file->grab();
//
//	th2->join();
//
////	pause();
//	//create player instance
////	irrgamePlayer* player = createIrrgamePlayer();
//
////	player->readConfig("");
////	IXMLReaderUTF8* xml = player->getFileSystem()->createXMLReaderUTF8("./assets/config.xml");
//
////	if(!xml)
////	{
////		player->drop();
////		return 0;
////	}
//
////read  config
//
////get pointer to game lib
////	void* app_handle;
////	app_handle = dlopen("../../thegame/", RTLD_LAZY);
//
////get application pointer
//
////irrgameApp app = new irrgameApp(player instance);
////app->run();
//
////onApplicationSuspend();
//
////	void * my_lib_handle;
////	int (*some_func)();
////
////		my_lib_handle = dlopen("libmylib.so",RTLD_NOW);
////		if(my_lib_handle==NULL) {
////			/* ERROR HANDLING */
////		}
////		some_func = (int (*)()) dlsym(my_lib_handle,"some_function");
////		if(some_func==NULL) {
////			/* ERROR HANDLING */
////		}
////		printf("Return code is %i\n",(*some_func)());
//
////irrgameThread::sleep();
//	return 0;
//}

