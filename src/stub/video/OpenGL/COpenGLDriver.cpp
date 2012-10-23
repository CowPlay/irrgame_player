/*
 * COpenGLDriver.cpp
 *
 *  Created on: Oct 11, 2012
 *      Author: gregorytkach
 */

#include "COpenGLDriver.h"

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>

namespace irrgame
{
	namespace video
	{
		//! Default constructor
		COpenGLDriver::COpenGLDriver(irrgamePlayer* player) :
				CNullDriver(player)
		{

		}

		//! Destructor
		COpenGLDriver::~COpenGLDriver()
		{

		}

		//! Applications must call this method before performing any rendering.
		void COpenGLDriver::beginScene(SColor color, bool backBuffer,
				bool zBuffer, recti* sourceRect)
		{
			CNullDriver::beginScene(color, backBuffer, zBuffer, sourceRect);

			//	changeRenderContext(videoData, Device);

			//	clearBuffers(backBuffer, zBuffer, false, color);
		}

//		//! Presents the rendered image to the screen.
//		void COpenGLDriver::endScene()
//		{
//			//	CNullDriver::endScene();
//			//
//			//	glFlush();
//			//
//			//#ifdef _IRR_COMPILE_WITH_WINDOWS_DEVICE_
//			//	if (DeviceType == EIDT_WIN32)
//			//		return SwapBuffers(HDc) == TRUE;
//			//#endif
//			//
//			//#ifdef _IRR_COMPILE_WITH_X11_DEVICE_
//			//	if (DeviceType == EIDT_X11)
//			//	{
//			//		glXSwapBuffers(X11Display, Drawable);
//			//		return true;
//			//	}
//			//#endif
//			//
//			//#ifdef _IRR_COMPILE_WITH_OSX_DEVICE_
//			//	if (DeviceType == EIDT_OSX)
//			//	{
//			//		Device->flush();
//			//		return true;
//			//	}
//			//#endif
//			//
//			//#ifdef _IRR_COMPILE_WITH_SDL_DEVICE_
//			//	if (DeviceType == EIDT_SDL)
//			//	{
//			//		SDL_GL_SwapBuffers();
//			//		return true;
//			//	}
//			//#endif
//			//
//			//	// todo: console device present
//			//
//		}

//! VideoDriver creator
		IVideoDriver* createVideoDriver(irrgamePlayer* player)
		{
			return new COpenGLDriver(player);
		}

	} /* namespace video */
} /* namespace irrgame */
