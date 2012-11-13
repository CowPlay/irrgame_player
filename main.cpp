/*
 * main.cpp
 *
 *  Created on: Jul 24, 2012
 *      Author: gregorytkach
 */
#include "irrgame.h"
#include "playerConstants.h"

using namespace irrgame;

using namespace events;
using namespace io;
using namespace threads;
using namespace video;

#include <stdio.h>
#include <dlfcn.h>

#include <typeinfo>

arrayi mass;

int some(int a)
{
	return 0;
}

#define signature_app_creator irrgameApp* (*)()

int main()
{

	typedef delegate<int, int> Tdel;

	Tdel* d = new Tdel;

	(*d) += NewDelegate(&some);
	(*d) += NewDelegate(&some);
	(*d) += NewDelegate(&some);

	(*d) -= NewDelegate(&some);

	irrgamePlayer * player = createIrrgamePlayer();

	player->getConfigReader()->read(FILE_CONFIG);

	void* appHandle = 0;

	irrgameApp* (*createIrrgameApp)();

	//open your application as static lib
	appHandle = dlopen(player->getConfigReader()->getEntry()->AppFile.cStr(),
			RTLD_NOW);

	c8* error = 0;
	error = dlerror();
	IRR_ASSERT(error == 0);

	createIrrgameApp = (signature_app_creator) dlsym(appHandle,
			player->getConfigReader()->getEntry()->AppCreator.cStr());

	error = dlerror();
	IRR_ASSERT(error == 0);

	irrgameApp* app = createIrrgameApp();

	IRR_ASSERT(app != 0);

	player->run(app);
}

//#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
//#include <GLUT/glut.h>
//#define window_width  640
//#define window_height 480
//// Main loop
//void main_loop_function() {
//    // Z angle
//    static float angle;
//    // Clear color (screen)
//    // And depth (used internally to block obstructed objects)
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    // Load identity matrix
//    glLoadIdentity();
//    // Multiply in translation matrix
//    glTranslatef(0, 0, -10);
//    // Multiply in rotation matrix
//    glRotatef(angle, 0, 0, 1);
//    // Render colored quad
//    glBegin( GL_QUADS);
//    glColor3ub(255, 000, 000);
//    glVertex2f(-1, 1);
//    glColor3ub(000, 255, 000);
//    glVertex2f(1, 1);
//    glColor3ub(000, 000, 255);
//    glVertex2f(1, -1);
//    glColor3ub(255, 255, 000);
//    glVertex2f(-1, -1);
//    glEnd();
//    // Swap buffers (color buffers, makes previous render visible)
//    glutSwapBuffers();
//    // Increase angle to rotate
//    angle += 0.25;
//}
//// Initialze OpenGL perspective matrix
//void GL_Setup(int width, int height) {
//    glViewport(0, 0, width, height);
//    glMatrixMode( GL_PROJECTION);
//    glEnable( GL_DEPTH_TEST);
//    gluPerspective(45, (float) width / height, .1, 100);
//    glMatrixMode( GL_MODELVIEW);
//}
//// Initialize GLUT and start main loop
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitWindowSize(window_width, window_height);
//    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
//    glutCreateWindow("GLUT Example!!!");
//    glutDisplayFunc(main_loop_function);
//    glutIdleFunc(main_loop_function);
//    GL_Setup(window_width, window_height);
//    glutMainLoop();
//}

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

