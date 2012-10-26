/*
 * COpenGLDriver.cpp
 *
 *  Created on: Oct 11, 2012
 *      Author: gregorytkach
 */

#include "COpenGLDriver.h"
#include "COpenGLExtensionHandler.h"
#include "video/ITexture.h"

namespace irrgame
{
	namespace video
	{
		//! Default constructor
		COpenGLDriver::COpenGLDriver(irrgamePlayer* player) :
				CNullDriver(player)
		{
			genericDriverInit();
		}

		bool COpenGLDriver::genericDriverInit()
		{
			dimension2du screenSize(100, 100);
			bool stencilBuffer = false;

//			u32 i;
//			for (i = 0; i < MATERIAL_MAX_TEXTURES; ++i)
//				CurrentTexture[i] = 0;
//			// load extensions

			COpenGLExtensionHandler::getInstance().initExtensions(false); // false to init stencil buffer extension

			glPixelStorei(GL_PACK_ALIGNMENT, 1);

			// Reset The Current Viewport
			glViewport(0, 0, screenSize.Width, screenSize.Height);

			UserClipPlanes.reallocate(
					COpenGLExtensionHandler::getInstance().MaxUserClipPlanes);
			for (s32 i = 0;
					i < COpenGLExtensionHandler::getInstance().MaxUserClipPlanes;
					++i)
			{
				UserClipPlanes.pushBack(SUserClipPlane());
			}

			for (s32 i = 0; i < ETS_COUNT; ++i)
			{
				//TODO: make it static to prevent duplicates creation
				matrix4 identity;
				setTransform(static_cast<ETransformationState>(i), identity);
			}

			//TODO: implement it
			//setAmbientLight(SColorf(0.0f, 0.0f, 0.0f, 0.0f));

			//TODO: implement it
//#ifdef GL_EXT_separate_specular_color
//			if (FeatureAvailable[IRR_EXT_separate_specular_color])
//				glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,
//						GL_SEPARATE_SPECULAR_COLOR);
//#endif
			glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

			// This is a fast replacement for NORMALIZE_NORMALS
			// if ((Version>101) || FeatureAvailable[IRR_EXT_rescale_normal])
			//  glEnable(GL_RESCALE_NORMAL_EXT);

			glClearDepth(1.0);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
			glDepthFunc(GL_LEQUAL);
			glFrontFace(GL_CW);

			// adjust flat coloring scheme to DirectX verssion

			//TODO: implement it
//#if defined(GL_ARB_provoking_vertex) || defined(GL_EXT_provoking_vertex)
//			extGlProvokingVertex(GL_FIRST_VERTEX_CONVENTION_EXT);
//#endif

			// create material renderers

			//TODO: implement it
			//createMaterialRenderers();

			// set the renderstates
			setRenderStates3DMode();

			glAlphaFunc(GL_GREATER, 0.f);

			// set fog mode

			//TODO: implement it
			//setFog(FogColor, FogType, FogStart, FogEnd, FogDensity, PixelFog,RangeFog);

			// create matrix for flipping textures

			//TODO: implement it
			//TextureFlipMatrix.buildTextureTransform(0.0f, vector2df(0, 0), vector2df(0, 1.0f), vector2df(1.0f, -1.0f));

			// We need to reset once more at the beginning of the first rendering.
			// This fixes problems with intermediate changes to the material during texture load.
			ResetRenderStates = true;

			return true;
		}

		//! sets the needed renderstates
		void COpenGLDriver::setRenderStates3DMode()
		{
			if (CurrentRenderMode != ERM_3D)
			{
				// Reset Texture Stages
				glDisable(GL_BLEND);
				glDisable(GL_ALPHA_TEST);
				glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

				// switch back the matrices
				glMatrixMode(GL_MODELVIEW);
				glLoadMatrixf(
						(Matrices[ETS_VIEW] * Matrices[ETS_WORLD]).pointer());

				GLfloat glmat[16];
				createGLMatrix(glmat, Matrices[ETS_PROJECTION]);
				glmat[12] *= -1.0f;
				glMatrixMode(GL_PROJECTION);
				glLoadMatrixf(glmat);

				ResetRenderStates = true;
			}

//TODO: implement
			/*
			 if (ResetRenderStates || LastMaterial != Material)
			 {
			 // unset old material

			 if (LastMaterial.MaterialType != Material.MaterialType &&
			 static_cast<u32>(LastMaterial.MaterialType) < MaterialRenderers.size())
			 MaterialRenderers[LastMaterial.MaterialType].Renderer->OnUnsetMaterial();

			 // set new material.
			 if (static_cast<u32>(Material.MaterialType) < MaterialRenderers.size())
			 MaterialRenderers[Material.MaterialType].Renderer->OnSetMaterial(
			 Material, LastMaterial, ResetRenderStates, this);

			 LastMaterial = Material;
			 ResetRenderStates = false;
			 }

			 if (static_cast<u32>(Material.MaterialType) < MaterialRenderers.size())
			 MaterialRenderers[Material.MaterialType].Renderer->OnRender(this, video::EVT_STANDARD);

			 CurrentRenderMode = ERM_3D;
			 */
		}

		//! creates a matrix in supplied GLfloat array to pass to OpenGL
		inline void COpenGLDriver::createGLMatrix(GLfloat gl_matrix[16],
				const matrix4& m)
		{
			memcpy(gl_matrix, m.pointer(), 16 * sizeof(f32));
		}

		//! sets transformation
		void COpenGLDriver::setTransform(ETransformationState state,
				const matrix4& mat)
		{
			Matrices[state] = mat;
			Transformation3DChanged = true;

			switch (state)
			{
				case ETS_VIEW:
				case ETS_WORLD:
				{
					// OpenGL only has a model matrix, view and world is not existent. so lets fake these two.
					glMatrixMode(GL_MODELVIEW);
					glLoadMatrixf(
							(Matrices[ETS_VIEW] * Matrices[ETS_WORLD]).pointer());
					// we have to update the clip planes to the latest view matrix
					for (u32 i = 0;
							i
									< IOpenGLExtensionHandler::getInstance().MaxUserClipPlanes;
							++i)
						if (UserClipPlanes[i].Enabled)
							uploadClipPlane(i);
				}
					break;
				case ETS_PROJECTION:
				{
					GLfloat glmat[16];
					createGLMatrix(glmat, mat);
					// flip z to compensate OpenGLs right-hand coordinate system
					glmat[12] *= -1.0f;
					glMatrixMode(GL_PROJECTION);
					glLoadMatrixf(glmat);
				}
					break;
				case ETS_COUNT:
					return;
				default:
				{
					// TODO: implement/refactor it
					/*
					 const u32 i = state - ETS_TEXTURE_0;
					 if (i >= MaterialMaxTextures)
					 break;

					 const bool isRTT = Material.getTexture(i)
					 && Material.getTexture(i)->isRenderTarget();

					 if (MultiTextureExtension)
					 extGlActiveTexture(GL_TEXTURE0_ARB + i);

					 glMatrixMode(GL_TEXTURE);
					 if (!isRTT && mat.isIdentity())
					 glLoadIdentity();
					 else
					 {
					 GLfloat glmat[16];
					 if (isRTT)
					 createGLTextureMatrix(glmat,
					 mat * TextureFlipMatrix);
					 else
					 createGLTextureMatrix(glmat, mat);

					 glLoadMatrixf(glmat);
					 }
					 */
					break;
				}
			}
		}

		void COpenGLDriver::uploadClipPlane(u32 index)
		{
			// opengl needs an array of doubles for the plane equation
			double clip_plane[4];
			clip_plane[0] = UserClipPlanes[index].Plane.Normal.X();
			clip_plane[1] = UserClipPlanes[index].Plane.Normal.Y();
			clip_plane[2] = UserClipPlanes[index].Plane.Normal.Z();
			clip_plane[3] = UserClipPlanes[index].Plane.D;
			glClipPlane(GL_CLIP_PLANE0 + index, clip_plane);
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

			clearBuffers(backBuffer, zBuffer, false, color);
		}

		//! Presents the rendered image to the screen.
		void COpenGLDriver::endScene()
		{
			CNullDriver::endScene();

			glFlush();

			Player->flush();

		}

		//! clears the zbuffer and color buffer
		void COpenGLDriver::clearBuffers(bool backBuffer, bool zBuffer,
				bool stencilBuffer, SColor color)
		{
			GLbitfield mask = 0;
			if (backBuffer)
			{
				const f32 inv = 1.0f / 255.0f;
				glClearColor(color.getRed() * inv, color.getGreen() * inv,
						color.getBlue() * inv, color.getAlpha() * inv);

				mask |= GL_COLOR_BUFFER_BIT;
			}

			if (zBuffer)
			{
				glDepthMask(GL_TRUE);
				//TODO: add support of it
				//LastMaterial.ZWriteEnable = true;
				mask |= GL_DEPTH_BUFFER_BIT;
			}

			if (stencilBuffer)
				mask |= GL_STENCIL_BUFFER_BIT;

			if (mask)
				glClear(mask);
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
