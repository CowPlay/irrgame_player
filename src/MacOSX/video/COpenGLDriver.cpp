/*
 * COpenGLDriver.cpp
 *
 *  Created on: Oct 16, 2012
 *      Author: gregorytkach
 */

#include "playerCompileConfig.h"

#ifdef _IRRGAME_MACOSX_
#ifdef VIDEO_DRIVER_OPENGL


#include "stub/video/OpenGL/COpenGLDriver.h"

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>

namespace irrgame
{
	namespace video
	{
		//! Presents the rendered image to the screen.
		void COpenGLDriver::endScene()
		{
			CNullDriver::endScene();

			glFlush();

			Player->flush();

		}

	}	// namespace video

}  // namespace irrgame

#endif //VIDEO_DRIVER_OPENGL
#endif //_IRRGAME_MACOSX_
