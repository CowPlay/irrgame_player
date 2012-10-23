/*
 * irrgamePlayerMac.h
 *
 *  Created on: Oct 18, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMEPLAYERMAC_H_
#define IRRGAMEPLAYERMAC_H_

#include "stub/irrgamePlayerStub.h"
#include "core/irrgamecollections.h"

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>

#include <objc/objc.h>

namespace irrgame
{
	class irrgamePlayerMac: public irrgamePlayerStub
	{
		public:
			//! Default consructor
			irrgamePlayerMac();

			//! Destructor
			virtual ~irrgamePlayerMac();

			void flush();

		protected:

			//! Run player internal. Must be overriden in every realization of player.
			//! Handle user events in this func
			bool runInternal();

		private:

			void createWindow();

		private:
			//pointer to window
			id Window;
			//pointer to CGL context
			CGLContextObj CGLContext;
			//pointer to OpenGL context
			id OGLContext;


			bool IsActive;
	};

} /* namespace irrgame */
#endif /* IRRGAMEPLAYERMAC_H_ */
