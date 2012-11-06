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
#include "video/material/SMaterial.h"
#include "ERenderTarget.h"
#include "ERenderMode.h"

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>

namespace irrgame
{
	namespace video
	{
		//! Implementation of OpenGL driver
		/*
		 * IMPORTANT! This class implement specification of OpenGL at least v2.0 ES
		 */
		class COpenGLDriver: public CNullDriver
		{
			public:
				//! Default constructor
				COpenGLDriver(irrgamePlayer* player);

				//!Destructor
				virtual ~COpenGLDriver();

				//! Applications must call this method before performing any rendering.
				virtual void beginScene(SColor color, bool backBuffer,
						bool zBuffer, recti* sourceRect);

				//! Presents the rendered image to the screen.
				//! Must be overriden for every player realization
				virtual void endScene();

				//! Sets the fog mode.
				virtual void setFog(FogEntry* value);

				//! set or reset render target
				bool setRenderTarget(ITexture* texture, bool clearBackBuffer,
						bool clearZBuffer, SColor color);

				//! Draws a pixel.
				virtual void drawPixel(u32 x, u32 y, const SColor &color);

				//! draws a 2d image, using a color and the alpha channel of the texture if
				//! desired. The image is drawn at pos, clipped against clipRect (if != 0).
				//! Only the subtexture defined by sourceRect is used.
				void draw2DImage(const video::ITexture* texture,
						const vector2di& pos, const recti& sourceRect,
						const recti* clipRect, SColor color,
						bool useAlphaChannelOfTexture);

				//! get render target size
				const dimension2du& getCurrentRenderTargetSize() const;

				//! sets the current Texture
				//! Returns whether setting was a success or not.
				bool setActiveTexture(u32 stage, const ITexture* texture);

				//! Returns the maximum texture size supported.
				virtual dimension2du getMaxTextureSize() const;

				//! Returns true if OpenGL have errors.
				virtual bool haveError() const;

			private:

				bool genericDriverInit();

				void clearBuffers(bool backBuffer, bool zBuffer,
						bool stencilBuffer, SColor color);

				//! Sets transformation matrices.
				/** \param state Transformation type to be set, e.g. view,
				 world, or projection.
				 \param mat Matrix describing the transformation. */
				void setTransform(ETransformationState state,
						const matrix4f& mat);

				//! sets the needed renderstates
				void setRenderStates3DMode();
				void setRenderStates2DMode(bool alpha, bool texture,
						bool alphaChannel);

				//! creates a transposed matrix in supplied GLfloat array to pass to OpenGL
				inline void createGLMatrix(GLfloat gl_matrix[16],
						const matrix4f& m);
				inline void createGLTextureMatrix(GLfloat gl_matrix[16],
						const matrix4f& m);

				//! apply prepared clip plane
				void uploadClipPlane(u32 index);

				//! create all material renderers
				void createMaterialRenderers();

				//! disables all textures beginning with the optional fromStage parameter. Otherwise all texture stages are disabled.
				//! Returns whether disabling was successful or not.
				bool disableTextures(u32 fromStage = 0);

			private:
				core::array<SUserClipPlane> UserClipPlanes;

				//! bool to make all renderstates reset if set to true.
				//TODO: review, mb need delete
				bool ResetRenderStates;
				ERenderMode CurrentRenderMode;
				matrix4f Matrices[ETS_COUNT];
				matrix4f TextureFlipMatrix;
				bool Transformation3DChanged;

				//! Texture buffers
				const ITexture* CurrentTexture[MaterialMaxTextures];

				//TODO:make comment
				ERenderTarget CurrentTarget;
				//TODO:make comment
				ITexture* RenderTargetTexture;
				//TODO:make comment
				dimension2du CurrentRendertargetSize;

				//TODO:make comment
				SMaterial Material;
				//TODO:make comment
				SMaterial LastMaterial;

				//TODO:make comment
				bool Doublebuffer;
				//TODO:make comment
				bool Stereo;

		};
	} /* namespace video */
} /* namespace irrgame */

#endif /* VIDEO_DRIVER_OPENGL */
#endif /* COPENGLDRIVER_H_ */
