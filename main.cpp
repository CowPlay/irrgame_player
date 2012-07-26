/*
 * main.cpp
 *
 *  Created on: Jul 24, 2012
 *      Author: gregorytkach
 */
#include "irrgame.h"

using namespace irrgame;

using namespace io;

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
//      exit(1);
//   }
//
//   fn = dlsym(lib_handle, "ctest1");
//   if ((error = dlerror()) != NULL)
//   {
//      fprintf(stderr, "%s\n", error);
//      exit(1);
//   }
//
//   (*fn)(&x);
//   printf("Valx=%d\n",x);
//
//   dlclose(lib_handle);
//   return 0;
//}


int main()
{
	irrgamePlayer* player = createIrrgamePlayer();
	//create player instance

	//read  config

	//get pointer to game lib
	void* app_handle;
	app_handle = dlopen("../../thegame/", RTLD_LAZY);

	//get application pointer

	//irrgameApp app = new irrgameApp(player instance);
	//app->run();


	//onApplicationSusped();



//	void * my_lib_handle;
//	int (*some_func)();
//
//		my_lib_handle = dlopen("libmylib.so",RTLD_NOW);
//		if(my_lib_handle==NULL) {
//			/* ERROR HANDLING */
//		}
//		some_func = (int (*)()) dlsym(my_lib_handle,"some_function");
//		if(some_func==NULL) {
//			/* ERROR HANDLING */
//		}
//		printf("Return code is %i\n",(*some_func)());



	return 0;
}



