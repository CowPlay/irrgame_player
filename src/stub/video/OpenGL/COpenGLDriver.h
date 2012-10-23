/*
 * COpenGLDriver.h
 *
 *  Created on: Oct 11, 2012
 *      Author: gregorytkach
 */

#ifndef COPENGLDRIVER_H_
#define COPENGLDRIVER_H_

#include "playerCompileConfig.h"

#ifdef VIDEO_DRIVER_OPENGL

#include "irrgamePlayer.h"

#include "stub/video/Null/CNullDriver.h"

namespace irrgame
{
	namespace video
	{
		class COpenGLDriver: public CNullDriver
		{
			public:
				//! Default constructor
				COpenGLDriver(irrgamePlayer* player);

				//!Destructor
				virtual ~COpenGLDriver();

				//! Applications must call this method before performing any rendering.
				/** This method can clear the back- and the z-buffer.
				 \param color The color used for back buffer clearing
				 \param backBuffer Specifies if the back buffer should be
				 cleared, which means that the screen is filled with the color
				 specified. If this parameter is false, the back buffer will
				 not be cleared and the color parameter is ignored.
				 \param zBuffer Specifies if the depth buffer (z buffer) should
				 be cleared. It is not nesesarry to do so if only 2d drawing is
				 used.
				 \param sourceRect Pointer to a rectangle defining the source
				 rectangle of the area to be presented. Set to null to present
				 everything. Note: not implemented in all devices.
				 */
				virtual void beginScene(SColor color = SColor(255, 0, 0, 0),
						bool backBuffer = true, bool zBuffer = true,
						recti* sourceRect = 0);

				//! Presents the rendered image to the screen.
				//! Must be overriden for every player realization
				/** Applications must call this method after performing any
				 rendering.
				 */
				virtual void endScene();
		};
	} /* namespace video */
} /* namespace irrgame */

#endif /* VIDEO_DRIVER_OPENGL */
#endif /* COPENGLDRIVER_H_ */
