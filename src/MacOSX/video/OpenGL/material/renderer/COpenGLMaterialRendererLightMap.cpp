/*
 * COpenGLMaterialRendererLightmap.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "COpenGLMaterialRendererLightmap.h"

namespace irrgame
{
	namespace video
	{

		//! Default constructor
		COpenGLMaterialRendererLightMap::COpenGLMaterialRendererLightMap(
				IVideoDriver* driver) :
				COpenGLMaterialRenderer(driver)
		{
		}

		//! Destructor
		COpenGLMaterialRendererLightMap::~COpenGLMaterialRendererLightMap()
		{
		}

		//! Called by the IVideoDriver implementation the let the renderer set its needed render states.
		void COpenGLMaterialRendererLightMap::OnSetMaterial(
				const SMaterial& material, const SMaterial& lastMaterial,
				bool resetAllRenderstates, IMaterialRendererServices* services)
		{
			//					Driver->disableTextures(2);
			//					Driver->setBasicRenderStates(material, lastMaterial,
			//							resetAllRenderstates);
			//
			//					if (material.MaterialType != lastMaterial.MaterialType
			//							|| resetAllRenderstates)
			//					{
			//						// diffuse map
			//
			//						switch (material.MaterialType)
			//						{
			//							case EMT_LIGHTMAP_LIGHTING:
			//							case EMT_LIGHTMAP_LIGHTING_M2:
			//							case EMT_LIGHTMAP_LIGHTING_M4:
			//								glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			//										GL_MODULATE);
			//								break;
			//							case EMT_LIGHTMAP_ADD:
			//							case EMT_LIGHTMAP:
			//							case EMT_LIGHTMAP_M2:
			//							case EMT_LIGHTMAP_M4:
			//							default:
			//								glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			//										GL_REPLACE);
			//								break;
			//						}
			//
			//						if (Driver->queryFeature(EVDF_MULTITEXTURE))
			//						{
			//							// lightmap
			//
			//							Driver->extGlActiveTexture(GL_TEXTURE1_ARB);
			//#ifdef GL_ARB_texture_env_combine
			//							glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			//									GL_COMBINE_ARB);
			//
			//							if (material.MaterialType == EMT_LIGHTMAP_ADD)
			//							glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB,
			//									GL_ADD);
			//							else
			//							glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB,
			//									GL_MODULATE);
			//
			//							glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB,
			//									GL_PREVIOUS_ARB);
			//							glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB,
			//									GL_TEXTURE);
			//							glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB,
			//									GL_MODULATE);
			//							glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_ARB,
			//									GL_PREVIOUS_ARB);
			//							glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_ARB,
			//									GL_PREVIOUS_ARB);
			//#else
			//							glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			//									GL_COMBINE_EXT);
			//
			//							if (material.MaterialType == EMT_LIGHTMAP_ADD)
			//								glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT,
			//										GL_ADD);
			//							else
			//								glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT,
			//										GL_MODULATE);
			//
			//							glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT,
			//									GL_PREVIOUS_EXT);
			//							glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT,
			//									GL_TEXTURE);
			//							glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT,
			//									GL_MODULATE);
			//							glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT,
			//									GL_PREVIOUS_EXT);
			//							glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_EXT,
			//									GL_PREVIOUS_EXT);
			//#endif
			//
			//							switch (material.MaterialType)
			//							{
			//								case EMT_LIGHTMAP_M4:
			//								case EMT_LIGHTMAP_LIGHTING_M4:
			//#ifdef GL_ARB_texture_env_combine
			//									glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB,
			//											4.0f);
			//#else
			//									glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT,
			//											4.0f);
			//#endif
			//									break;
			//								case EMT_LIGHTMAP_M2:
			//								case EMT_LIGHTMAP_LIGHTING_M2:
			//#ifdef GL_ARB_texture_env_combine
			//									glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB,
			//											2.0f);
			//#else
			//									glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT,
			//											2.0f);
			//#endif
			//									break;
			//								default:
			//#ifdef GL_ARB_texture_env_combine
			//									glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB,
			//											1.0f);
			//#else
			//									glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT,
			//											1.0f);
			//#endif
			//							}
			//							Driver->extGlActiveTexture(GL_TEXTURE0_ARB);
			//						}
			//					}
		}

		//! Called by the IVideoDriver to unset this material.
		void COpenGLMaterialRendererLightMap::OnUnsetMaterial()
		{
			//					if (Driver->queryFeature(EVDF_MULTITEXTURE))
			//					{
			//						Driver->extGlActiveTexture(GL_TEXTURE1_ARB);
			//#ifdef GL_ARB_texture_env_combine
			//						glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 1.f);
			//#else
			//						glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 1.f);
			//#endif
			//						glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			//								GL_MODULATE);
			//						Driver->extGlActiveTexture(GL_TEXTURE0_ARB);
			//						glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			//								GL_MODULATE);
			//					}
		}

		IMaterialRenderer* IMaterialRenderer::createMaterialRendererLightMap(IVideoDriver* driver)
		{
			return new COpenGLMaterialRendererLightMap(driver);
		}

	} /* namespace video */
} /* namespace irrgame */
