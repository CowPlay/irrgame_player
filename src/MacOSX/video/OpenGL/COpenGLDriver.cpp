/*
 * COpenGLDriver.cpp
 *
 *  Created on: Oct 11, 2012
 *      Author: gregorytkach
 */

#include "COpenGLDriver.h"

#include "video/ITexture.h"
#include "video/color/SColorf.h"

#include "SharedOpenGLExtensionHandler.h"
#include "COpenGLTexture.h"

//TODO: refactor
#include "material/renderer/COpenGLMaterialRenderer.h"
#include "material/renderer/COpenGLMaterialRendererDetailMap.h"
#include "material/renderer/COpenGLMaterialRendererLightMap.h"
#include "material/renderer/COpenGLMaterialRendererOneTextureBlend.h"
#include "material/renderer/COpenGLMaterialRendererReflection2Layer.h"
#include "material/renderer/COpenGLMaterialRendererSolid.h"
#include "material/renderer/COpenGLMaterialRendererSolid2Layer.h"
#include "material/renderer/COpenGLMaterialRendererSphereMap.h"
#include "material/renderer/COpenGLMaterialRendererTransparentAddColor.h"
#include "material/renderer/COpenGLMaterialRendererTransparentAlphaChannel.h"
#include "material/renderer/COpenGLMaterialRendererTransparentAlphaChannelRef.h"
#include "material/renderer/COpenGLMaterialRendererTransparentReflection2Layer.h"
#include "material/renderer/COpenGLMaterialRendererTransparentVertexAlpha.h"

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

		//! Sets the fog mode.
		//TODO: make struct for fog
		void COpenGLDriver::setFog(FogEntry* value)
		{
			//this->Fog = value
			CNullDriver::setFog(value);

			// Fog type
			// Calculates force of fog depending from range by this formula
			glFogf(GL_FOG_MODE,
					GLfloat(
							(Fog->Type == EFT_FOG_LINEAR) ? GL_LINEAR :
							(Fog->Type == EFT_FOG_EXP) ? GL_EXP : GL_EXP2));

			// Checking if fog as a object supported
			if (SharedOpenGLExtensionHandler::getInstance().isOpenGLFeatureAvailable(
					IRR_EXT_fog_coord))
			{
				glFogi(GL_FOG_COORDINATE_SOURCE, GL_FRAGMENT_DEPTH);
			}

			// Fog can be a 2 types, as similar object of OpenGL or like a "Pixel effect" on camera
			// Here is configuring of params
			if (Fog->Type == EFT_FOG_LINEAR)
			{
				glFogf(GL_FOG_START, Fog->Start);
				glFogf(GL_FOG_END, Fog->End);
			}
			else
			{
				glFogf(GL_FOG_DENSITY, Fog->Density);
			}

			// Interpolation quality of fog setup here
			if (Fog->PixelFog)
			{
				glHint(GL_FOG_HINT, GL_NICEST);
			}
			else
			{
				glHint(GL_FOG_HINT, GL_FASTEST);
			}

			// Converting of internal color to OpenGL format
			SColorf color(Fog->Color);
			GLfloat data[4] =
			{ color.Red, color.Green, color.Blue, color.Alpha };

			// Setting for color
			glFogfv(GL_FOG_COLOR, data);
		}

		bool COpenGLDriver::genericDriverInit()
		{

			//TODO: refactor it, make it depended from window size
			//TODO: make Screensize loaded from config
			dimension2du screenSize(800, 600);
			ScreenSize = screenSize;

			//TODO: read it from config
			bool stencilBuffer = false;

			//FIXME
			//for (s32 i = 0; i < MaterialMaxTextures; ++i)
//				CurrentTexture[i] = 0;
//			// load extensions

			//
			SharedOpenGLExtensionHandler::getInstance().initExtensions(
					stencilBuffer);

			// Setting the bit-packing style for row of pixels (memory alignment)
			glPixelStorei(GL_PACK_ALIGNMENT, 1);

			// Reset The Current Viewport
			glViewport(0, 0, screenSize.Width, screenSize.Height);

			// Setup 3D clipping planes for reducing objects calculation
			UserClipPlanes.reallocate(
					SharedOpenGLExtensionHandler::getInstance().MaxUserClipPlanes);
			for (s32 i = 0;
					i
							< SharedOpenGLExtensionHandler::getInstance().MaxUserClipPlanes;
					++i)
			{
				UserClipPlanes.pushBack(SUserClipPlane());
			}

			// Reset every transform matrixes for each context
			for (s32 i = 0; i < ETS_COUNT; ++i)
			{
				setTransform(static_cast<ETransformationState>(i),
						matrix4f::getIdentityMatrix());
			}

			//TODO: implement it
			//setAmbientLight(SColorf(0.0f, 0.0f, 0.0f, 0.0f));

			//TODO: implement it
//#ifdef GL_EXT_separate_specular_color
//			if (FeatureAvailable[IRR_EXT_separate_specular_color])
//				glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,
//						GL_SEPARATE_SPECULAR_COLOR);
//#endif
			// Light model calculations method for current view context
			// 0 - fastest
			// 1 - quality
			glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

			// This is a fast replacement for NORMALIZE_NORMALS
			// if ((Version>101) || FeatureAvailable[IRR_EXT_rescale_normal])
			//  glEnable(GL_RESCALE_NORMAL_EXT);

			// Value what will fill depth buffer at glClear function
			glClearDepth(1.0);

			// Configure interpolation quality
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);

			// Choose z-buffer method checking
			// GL_LEWQUAL - pass object if z <= cameras z
			glDepthFunc(GL_LEQUAL);

			// Choose edge faces render mode (clock-wise, classical)
			glFrontFace(GL_CW);

			// adjust flat coloring scheme to DirectX verssion

			//TODO: implement it
//#if defined(GL_ARB_provoking_vertex) || defined(GL_EXT_provoking_vertex)
//			extGlProvokingVertex(GL_FIRST_VERTEX_CONVENTION_EXT);
//#endif

			// create material renderers
			createMaterialRenderers();

			// set the renderstates (also we flipping z-axis here to redefine "Z-depth" as "Z-height")
			setRenderStates3DMode();

			// Alpha checking function (if alpha exist)
			glAlphaFunc(GL_GREATER, 0.f);

			// set fog mode
			FogEntry* fog = new FogEntry();
			setFog(fog);
			fog->drop();

			// create matrix for flipping textures
			TextureFlipMatrix.buildTextureTransform(0.0f, vector2df(0, 0),
					vector2df(0, 1.0f), vector2df(1.0f, -1.0f));

			// We need to reset once more at the beginning of the first rendering.
			// This fixes problems with intermediate changes to the material during texture load.
			ResetRenderStates = true;

			return true;
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

			// Z-Buffer clear
			if (zBuffer)
			{
				// Setting the depth buffer can be masked
				glDepthMask(GL_TRUE);
				//TODO: add support of it
				//LastMaterial.ZWriteEnable = true;
				mask |= GL_DEPTH_BUFFER_BIT;
			}

			// Stencil-Buffer clear
			if (stencilBuffer)
			{
				mask |= GL_STENCIL_BUFFER_BIT;
			}

			if (mask)
			{
				glClear(mask);
			}
		}

		//! Returns the maximum texture size supported.
		dimension2du COpenGLDriver::getMaxTextureSize() const
		{
			return dimension2du(
					SharedOpenGLExtensionHandler::getInstance().MaxTextureSize,
					SharedOpenGLExtensionHandler::getInstance().MaxTextureSize);
		}

		//! sets transformation
		void COpenGLDriver::setTransform(ETransformationState state,
				const matrix4f& mat)
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

					u32 maxUserClipPlanes =
							SharedOpenGLExtensionHandler::getInstance().MaxUserClipPlanes;

					// we have to update the clip planes to the latest view matrix
					for (u32 i = 0; i < maxUserClipPlanes; ++i)
					{
						if (UserClipPlanes[i].Enabled)
						{
							uploadClipPlane(i);
						}
					}
					break;
				}
				case ETS_PROJECTION:
				{
					GLfloat glmat[16];
					createGLMatrix(glmat, mat);
					// flip z to compensate OpenGLs right-hand coordinate system
					glmat[12] *= -1.0f;
					glMatrixMode(GL_PROJECTION);
					glLoadMatrixf(glmat);

					break;
				}
				default:
				{
					const u32 i = state - ETS_TEXTURE_0;

					IRR_ASSERT(i < ETS_COUNT);

					if (i < MaterialMaxTextures)
					{
						//we break it here because MaterialMaxTextures can be less than 8
						break;
					}

					const bool isRTT = Material.getTexture(i)
							&& Material.getTexture(i)->isRenderTarget();

					if (SharedOpenGLExtensionHandler::getInstance().MultiTextureExtension)
					{
						SharedOpenGLExtensionHandler::getInstance().extGlActiveTexture(
								GL_TEXTURE0_ARB + i);
					}

					glMatrixMode(GL_TEXTURE);
					if (!isRTT && mat.isIdentity())
					{
						glLoadIdentity();
					}
					else
					{
						GLfloat glmat[16];
						if (isRTT)
						{
							createGLTextureMatrix(glmat,
									mat * TextureFlipMatrix);
						}
						else
						{
							createGLTextureMatrix(glmat, mat);
						}

						glLoadMatrixf(glmat);
					}

					break;
				}
			}
		}

		//! Sets the needed renderstates
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

				// flip z to compensate OpenGLs right-hand coordinate system
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

		//! sets the needed renderstates
		void COpenGLDriver::setRenderStates2DMode(bool alpha, bool texture,
				bool alphaChannel)
		{
			if (CurrentRenderMode != ERM_2D || Transformation3DChanged)
			{
				// unset last 3d material
				if (CurrentRenderMode == ERM_3D)
				{
					if (static_cast<u32>(LastMaterial.MaterialType)
							< MaterialRenderers.size())
					{
						MaterialRenderers[LastMaterial.MaterialType]->OnUnsetMaterial();
					}
				}
				if (Transformation3DChanged)
				{
					glMatrixMode(GL_PROJECTION);

					const dimension2du& renderTargetSize =
							getCurrentRenderTargetSize();
					matrix4f m;
					m.buildProjectionMatrixOrthoLH(f32(renderTargetSize.Width),
							f32(-(s32) (renderTargetSize.Height)), -1.0, 1.0);
					m.setTranslation(vector3df(-1, 1, 0));
					glLoadMatrixf(m.pointer());

					glMatrixMode(GL_MODELVIEW);
					glLoadIdentity();
					glTranslatef(0.375, 0.375, 0.0);

					// Make sure we set first texture matrix
					if (SharedOpenGLExtensionHandler::getInstance().MultiTextureExtension)
					{
						SharedOpenGLExtensionHandler::getInstance().extGlActiveTexture(
								GL_TEXTURE0_ARB);
					}

					Transformation3DChanged = false;
				}
				//FIXME
//		       if (!OverrideMaterial2DEnabled)
//		       {
//		           setBasicRenderStates(InitMaterial2D, LastMaterial, true);
//		           LastMaterial = InitMaterial2D;
//		       }
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			//FIXME
//		   if (OverrideMaterial2DEnabled)
//		   {
//		       OverrideMaterial2D.Lighting=false;
//		       OverrideMaterial2D.ZBuffer=ECFN_NEVER;
//		       OverrideMaterial2D.ZWriteEnable=false;
//		       setBasicRenderStates(OverrideMaterial2D, LastMaterial, false);
//		       LastMaterial = OverrideMaterial2D;
//		   }

			if (alphaChannel || alpha)
			{
				glEnable(GL_BLEND);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER, 0.f);
			}
			else
			{
				glDisable(GL_BLEND);
				glDisable(GL_ALPHA_TEST);
			}

			if (texture)
			{
				//FIXME
//		       if (!OverrideMaterial2DEnabled)
//		       {
//		           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//		           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//		           glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		           glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		       }
				setTransform(ETS_TEXTURE_0, matrix4f::getIdentityMatrix());

				if (alphaChannel)
				{
					// if alpha and alpha texture just modulate, otherwise use only the alpha channel
					if (alpha)
					{
						glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
								GL_MODULATE);
					}
					else
					{
						if (SharedOpenGLExtensionHandler::getInstance().isOpenGLFeatureAvailable(
								IRR_ARB_texture_env_combine)
								|| SharedOpenGLExtensionHandler::getInstance().isOpenGLFeatureAvailable(
										IRR_EXT_texture_env_combine))
						{
							glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
									GL_COMBINE_ARB);
							glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB,
									GL_REPLACE);
							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_ARB,
									GL_TEXTURE);
							// rgb always modulates
							glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB,
									GL_MODULATE);
							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB,
									GL_TEXTURE);
							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB,
									GL_PRIMARY_COLOR_ARB);
						}
						else
						{
							glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
									GL_MODULATE);
						}
					}
				}
				else
				{
					if (alpha)
					{
						if (SharedOpenGLExtensionHandler::getInstance().isOpenGLFeatureAvailable(
								IRR_ARB_texture_env_combine)
								|| SharedOpenGLExtensionHandler::getInstance().isOpenGLFeatureAvailable(
										IRR_EXT_texture_env_combine))
						{
							glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
									GL_COMBINE_ARB);
							glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB,
									GL_REPLACE);
							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_ARB,
									GL_PRIMARY_COLOR_ARB);
							// rgb always modulates
							glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB,
									GL_MODULATE);
							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB,
									GL_TEXTURE);
							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB,
									GL_PRIMARY_COLOR_ARB);
						}
						else
						{
							glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
									GL_MODULATE);
						}
					}
					else
					{
						glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
								GL_MODULATE);
					}
				}
			}

			CurrentRenderMode = ERM_2D;
		}

		//! creates a matrix in supplied GLfloat array to pass to OpenGL
		inline void COpenGLDriver::createGLMatrix(GLfloat gl_matrix[16],
				const matrix4f& m)
		{
			memcpy(gl_matrix, m.pointer(), 16 * sizeof(f32));
		}

		//! creates a opengltexturematrix from a D3D style texture matrix
		inline void COpenGLDriver::createGLTextureMatrix(GLfloat *o,
				const matrix4f& m)
		{
			o[0] = m[0];
			o[1] = m[1];
			o[2] = 0.f;
			o[3] = 0.f;

			o[4] = m[4];
			o[5] = m[5];
			o[6] = 0.f;
			o[7] = 0.f;

			o[8] = 0.f;
			o[9] = 0.f;
			o[10] = 1.f;
			o[11] = 0.f;

			o[12] = m[8];
			o[13] = m[9];
			o[14] = 0.f;
			o[15] = 1.f;
		}

		//! Apply clip planes into OpenGL
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

		void COpenGLDriver::createMaterialRenderers()
		{
			// create OpenGL material renderers

			IMaterialRenderer* rendererSolid = new COpenGLMaterialRendererSolid(
					this);
			addMaterialRenderer(rendererSolid);
			rendererSolid->drop();

			IMaterialRenderer* rendererSolid2Layer =
					new COpenGLMaterialRendererSolid(this);
			addMaterialRenderer(rendererSolid2Layer);
			rendererSolid2Layer->drop();

			// add the same renderer for all lightmap types
			IMaterialRenderer* rendererLightMap =
					new COpenGLMaterialRendererLightMap(this);

			addMaterialRenderer(rendererLightMap); // for EMT_LIGHTMAP:
			addMaterialRenderer(rendererLightMap); // for EMT_LIGHTMAP_ADD:
			addMaterialRenderer(rendererLightMap); // for EMT_LIGHTMAP_M2:
			addMaterialRenderer(rendererLightMap); // for EMT_LIGHTMAP_M4:
			addMaterialRenderer(rendererLightMap); // for EMT_LIGHTMAP_LIGHTING:
			addMaterialRenderer(rendererLightMap); // for EMT_LIGHTMAP_LIGHTING_M2:
			addMaterialRenderer(rendererLightMap); // for EMT_LIGHTMAP_LIGHTING_M4:

			rendererLightMap->drop();

			// add remaining material renderer
			IMaterialRenderer* rendererDetailMap =
					new COpenGLMaterialRendererDetailMap(this);
			addMaterialRenderer(rendererDetailMap);
			rendererDetailMap->drop();

			IMaterialRenderer* rendererSphereMap =
					new COpenGLMaterialRendererDetailMap(this);
			addMaterialRenderer(rendererSphereMap);
			rendererSphereMap->drop();

			IMaterialRenderer* rendererReflection2Layer =
					new COpenGLMaterialRendererReflection2Layer(this);
			addMaterialRenderer(rendererReflection2Layer);
			rendererReflection2Layer->drop();

			IMaterialRenderer* rendererTransparentAddColor =
					new COpenGLMaterialRendererTransparentAddColor(this);
			addMaterialRenderer(rendererTransparentAddColor);
			rendererTransparentAddColor->drop();

			IMaterialRenderer* rendererTransparentAlphaChannel =
					new COpenGLMaterialRendererTransparentAlphaChannel(this);
			addMaterialRenderer(rendererTransparentAlphaChannel);
			rendererTransparentAlphaChannel->drop();

			IMaterialRenderer* rendererTransparentAlphaChannelRef =
					new COpenGLMaterialRendererTransparentAlphaChannelRef(this);
			addMaterialRenderer(rendererTransparentAlphaChannelRef);
			rendererTransparentAlphaChannelRef->drop();

			IMaterialRenderer* rendererTransparentVertexAlpha =
					new COpenGLMaterialRendererTransparentVertexAlpha(this);
			addMaterialRenderer(rendererTransparentVertexAlpha);
			rendererTransparentVertexAlpha->drop();

			IMaterialRenderer* rendererTransparentReflection2Layer =
					new COpenGLMaterialRendererTransparentReflection2Layer(
							this);
			addMaterialRenderer(rendererTransparentReflection2Layer);
			rendererTransparentReflection2Layer->drop();

			//TODO: implement when adds shader support
			//			// add normal map renderers
			//			s32 tmp = 0;
			//			video::IMaterialRenderer* renderer = 0;
			//			renderer = new COpenGLNormalMapRenderer(this, tmp,
			//					MaterialRenderers[EMT_SOLID].Renderer);
			//			renderer->drop();
			//			renderer = new COpenGLNormalMapRenderer(this, tmp,
			//					MaterialRenderers[EMT_TRANSPARENT_ADD_COLOR].Renderer);
			//			renderer->drop();
			//			renderer = new COpenGLNormalMapRenderer(this, tmp,
			//					MaterialRenderers[EMT_TRANSPARENT_VERTEX_ALPHA].Renderer);
			//			renderer->drop();
			//
			//			// add parallax map renderers
			//			renderer = new COpenGLParallaxMapRenderer(this, tmp,
			//					MaterialRenderers[EMT_SOLID].Renderer);
			//			renderer->drop();
			//			renderer = new COpenGLParallaxMapRenderer(this, tmp,
			//					MaterialRenderers[EMT_TRANSPARENT_ADD_COLOR].Renderer);
			//			renderer->drop();
			//			renderer = new COpenGLParallaxMapRenderer(this, tmp,
			//					MaterialRenderers[EMT_TRANSPARENT_VERTEX_ALPHA].Renderer);
			//			renderer->drop();
			//
			//			// add basic 1 texture blending
			//			addAndDropMaterialRenderer(
			//					new COpenGLMaterialRenderer_ONETEXTURE_BLEND(this));
		}

		//! set or reset render target
		bool COpenGLDriver::setRenderTarget(video::ITexture* texture,
				bool clearBackBuffer, bool clearZBuffer, SColor color)
		{
			// Check for right driver type. Possible only if unsupported by opengl texture want to load
			// example, d3d textures
			// texture can be NULL
			IRR_ASSERT(
					(texture == 0) || (texture && texture->getType() == EDT_OPENGL));

			// check if we should set the previous RT back

			setActiveTexture(0, 0);
			ResetRenderStates = true;

			if (RenderTargetTexture != 0)
			{
				// FIXME
				//RenderTargetTexture->unbindRTT();
			}

			if (texture)
			{
				// we want to set a new target. so do this.
				glViewport(0, 0, texture->getSize().Width,
						texture->getSize().Height);
				// FIXME
				RenderTargetTexture = texture;
				// FIXME
				//RenderTargetTexture->bindRTT();
				CurrentRendertargetSize = texture->getSize();
				CurrentTarget = ERT_RENDER_TEXTURE;
			}
			else
			{
				glViewport(0, 0, ScreenSize.Width, ScreenSize.Height);
				RenderTargetTexture = 0;
				CurrentRendertargetSize = dimension2du(0, 0);
				CurrentTarget = ERT_FRAME_BUFFER;
				glDrawBuffer(Doublebuffer ? GL_BACK_LEFT : GL_FRONT_LEFT);
			}

			clearBuffers(clearBackBuffer, clearZBuffer, false, color);
			return true;
		}

		//! disables all textures beginning with the optional fromStage parameter. Otherwise all texture stages are disabled.
		//! Returns whether disabling was successful or not.
		bool COpenGLDriver::disableTextures(u32 fromStage)
		{
			bool result = true;

			u8 maxTextureUnits =
					SharedOpenGLExtensionHandler::getInstance().MaxTextureUnits;

			for (u32 i = fromStage; i < maxTextureUnits; ++i)
			{
				result &= setActiveTexture(i, 0);
			}

			return result;
		}

		//! get render target size
		const dimension2du& COpenGLDriver::getCurrentRenderTargetSize() const
		{
			if (CurrentRendertargetSize.Width == 0)
			{
				return ScreenSize;
			}
			else
			{
				return CurrentRendertargetSize;
			}
		}

		//! Draws a pixel
		void COpenGLDriver::drawPixel(u32 x, u32 y, const SColor &color)
		{
			const dimension2du& renderTargetSize = getCurrentRenderTargetSize();

			IRR_ASSERT(
					x < (u32) renderTargetSize.Width && y < (u32) renderTargetSize.Height);

			disableTextures();
			setRenderStates2DMode(color.getAlpha() < 255, false, false);

			glBegin(GL_POINTS);
			glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
					color.getAlpha());
			glVertex2i(x, y);
			glEnd();
		}

		//! draws a 2d image, using a color and the alpha channel of the texture if
		//! desired. The image is drawn at pos, clipped against clipRect (if != 0).
		//! Only the subtexture defined by sourceRect is used.
		void COpenGLDriver::draw2DImage(const video::ITexture* texture,
				const vector2di& pos, const recti& sourceRect,
				const recti* clipRect, SColor color,
				bool useAlphaChannelOfTexture)
		{
			if (!texture)
				return;

			if (!sourceRect.isValid())
				return;

			vector2di targetPos(pos);
			vector2di sourcePos(sourceRect.UpperLeftCorner);
			// This needs to be signed as it may go negative.
			dimension2di sourceSize(sourceRect.getSize());
			if (clipRect)
			{
				if (targetPos.X() < clipRect->UpperLeftCorner.X())
				{
					sourceSize.Width += targetPos.X()
							- clipRect->UpperLeftCorner.X();
					if (sourceSize.Width <= 0)
						return;

					sourcePos.X() -= targetPos.X()
							- clipRect->UpperLeftCorner.X();
					targetPos.X() = clipRect->UpperLeftCorner.X();
				}

				if (targetPos.X() + sourceSize.Width
						> clipRect->LowerRightCorner.X())
				{
					sourceSize.Width -= (targetPos.X() + sourceSize.Width)
							- clipRect->LowerRightCorner.X();
					if (sourceSize.Width <= 0)
						return;
				}

				if (targetPos.Y() < clipRect->UpperLeftCorner.Y())
				{
					sourceSize.Height += targetPos.Y()
							- clipRect->UpperLeftCorner.Y();
					if (sourceSize.Height <= 0)
						return;

					sourcePos.Y() -= targetPos.Y()
							- clipRect->UpperLeftCorner.Y();
					targetPos.Y() = clipRect->UpperLeftCorner.Y();
				}

				if (targetPos.Y() + sourceSize.Height
						> clipRect->LowerRightCorner.Y())
				{
					sourceSize.Height -= (targetPos.Y() + sourceSize.Height)
							- clipRect->LowerRightCorner.Y();
					if (sourceSize.Height <= 0)
						return;
				}
			}

			// clip these coordinates

			if (targetPos.X() < 0)
			{
				sourceSize.Width += targetPos.X();
				if (sourceSize.Width <= 0)
					return;

				sourcePos.X() -= targetPos.X();
				targetPos.X() = 0;
			}

			const dimension2du& renderTargetSize = getCurrentRenderTargetSize();

			if (targetPos.X() + sourceSize.Width > (s32) renderTargetSize.Width)
			{
				sourceSize.Width -= (targetPos.X() + sourceSize.Width)
						- renderTargetSize.Width;
				if (sourceSize.Width <= 0)
					return;
			}

			if (targetPos.Y() < 0)
			{
				sourceSize.Height += targetPos.Y();
				if (sourceSize.Height <= 0)
					return;

				sourcePos.Y() -= targetPos.Y();
				targetPos.Y() = 0;
			}

			if (targetPos.Y() + sourceSize.Height
					> (s32) renderTargetSize.Height)
			{
				sourceSize.Height -= (targetPos.Y() + sourceSize.Height)
						- renderTargetSize.Height;
				if (sourceSize.Height <= 0)
					return;
			}

			// ok, we've clipped everything.
			// now draw it.

			// texcoords need to be flipped horizontally for RTTs
			const bool isRTT = texture->isRenderTarget();
			const dimension2du& ss = texture->getOriginalSize();
			const f32 invW = 1.f / static_cast<f32>(ss.Width);
			const f32 invH = 1.f / static_cast<f32>(ss.Height);
			const rectf tcoords(sourcePos.X() * invW,
					(isRTT ? (sourcePos.Y() + sourceSize.Height) : sourcePos.Y())
							* invH, (sourcePos.X() + sourceSize.Width) * invW,
					(isRTT ? sourcePos.Y() : (sourcePos.Y() + sourceSize.Height))
							* invH);

			const recti poss(targetPos, sourceSize);

			disableTextures(1);

			if (!setActiveTexture(0, texture))
			{
				return;
			}

			setRenderStates2DMode(color.getAlpha() < 255, true,
					useAlphaChannelOfTexture);

			glColor4ub(color.getRed(), color.getGreen(), color.getBlue(),
					color.getAlpha());
			glBegin(GL_QUADS);

			glTexCoord2f(tcoords.UpperLeftCorner.X(),
					tcoords.UpperLeftCorner.Y());
			glVertex2f(GLfloat(poss.UpperLeftCorner.X()),
					GLfloat(poss.UpperLeftCorner.Y()));

			glTexCoord2f(tcoords.LowerRightCorner.X(),
					tcoords.UpperLeftCorner.Y());
			glVertex2f(GLfloat(poss.LowerRightCorner.X()),
					GLfloat(poss.UpperLeftCorner.Y()));

			glTexCoord2f(tcoords.LowerRightCorner.X(),
					tcoords.LowerRightCorner.Y());
			glVertex2f(GLfloat(poss.LowerRightCorner.X()),
					GLfloat(poss.LowerRightCorner.Y()));

			glTexCoord2f(tcoords.UpperLeftCorner.X(),
					tcoords.LowerRightCorner.Y());
			glVertex2f(GLfloat(poss.UpperLeftCorner.X()),
					GLfloat(poss.LowerRightCorner.Y()));

			glEnd();
		}

		bool COpenGLDriver::setActiveTexture(u32 stage,
				const video::ITexture* texture)
		{
			if (stage
					>= SharedOpenGLExtensionHandler::getInstance().MaxTextureUnits)
			{
				return false;
			}

			//if (CurrentTexture[stage] == texture)
			//{
//				return true;
			//}

			if (SharedOpenGLExtensionHandler::getInstance().MultiTextureExtension)
			{
				SharedOpenGLExtensionHandler::getInstance().extGlActiveTexture(
						GL_TEXTURE0_ARB + stage);
			}

			CurrentTexture[stage] = texture;

			if (!texture)
			{
				glDisable(GL_TEXTURE_2D);
				return true;
			}
			else
			{

				if (texture->getType() != EDT_OPENGL)
				{
					glDisable(GL_TEXTURE_2D);
					// texture can't be load
					IRR_ASSERT(false);
					return false;
				}

				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,
						static_cast<const COpenGLTexture*>(texture)->getOpenGLTextureName());
			}
			return true;
		}

		//! Returns true if video driver have errors.
		bool COpenGLDriver::haveError() const
		{
			bool result = false;

			GLenum lastError = glGetError();

			switch (lastError)
			{
				case GL_NO_ERROR:
				{
					break;
				}
				case GL_INVALID_ENUM:
				case GL_INVALID_VALUE:
				case GL_INVALID_OPERATION:
				case GL_STACK_OVERFLOW:
				case GL_STACK_UNDERFLOW:
				case GL_OUT_OF_MEMORY:
				case GL_TABLE_TOO_LARGE:
				default:
				{
					IRR_ASSERT(false);
					result = true;
					break;
				}
			};

			return result;
		}

		//! VideoDriver creator
		IVideoDriver * createVideoDriver(irrgamePlayer * player)
		{
			return new COpenGLDriver(player);
		}

	} /* namespace video */
} /* namespace irrgame */
