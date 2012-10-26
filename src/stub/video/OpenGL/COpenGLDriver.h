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
#include "SUserClipPlane.h"
#include "video/ETransformationState.h"
#include "video/materials/SMaterial.h"
#include "ERenderMode.h"

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>

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

			private:
				void clearBuffers(bool backBuffer, bool zBuffer,
						bool stencilBuffer, SColor color);
				bool genericDriverInit();
				//! Sets transformation matrices.
				/** \param state Transformation type to be set, e.g. view,
				 world, or projection.
				 \param mat Matrix describing the transformation. */
				void setTransform(ETransformationState state,
						const matrix4& mat);
				//! sets the needed renderstates
				void setRenderStates3DMode();

				//! creates a transposed matrix in supplied GLfloat array to pass to OpenGL
				inline void createGLMatrix(GLfloat gl_matrix[16],
						const matrix4& m);

				//! apply prepared clip plane
				void uploadClipPlane(u32 index);

			private:
				core::array<SUserClipPlane> UserClipPlanes;

				//! bool to make all renderstates reset if set to true.
				bool ResetRenderStates;
				ERenderMode CurrentRenderMode;
				matrix4 Matrices[ETS_COUNT];
				bool Transformation3DChanged;

				SMaterial Material;
				SMaterial LastMaterial;

		};
	} /* namespace video */
} /* namespace irrgame */

#endif /* VIDEO_DRIVER_OPENGL */
#endif /* COPENGLDRIVER_H_ */
