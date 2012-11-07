/*
 * COpenGLMaterialRendererDetailmap.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "COpenGLMaterialRendererDetailmap.h"

namespace irrgame
{
	namespace video
	{
		//! Default constructor
		COpenGLMaterialRendererDetailMap::COpenGLMaterialRendererDetailMap(
				IVideoDriver* driver) :
				COpenGLMaterialRenderer(driver)
		{
		}

		//! Destructor
		COpenGLMaterialRendererDetailMap::~COpenGLMaterialRendererDetailMap()
		{
		}

		//! Called by the IVideoDriver implementation the let the renderer set its needed render states.
		void COpenGLMaterialRendererDetailMap::OnSetMaterial(
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
			//						// diffuse map is default modulated
			//
			//						// detail map on second layer
			//						if (Driver->queryFeature(EVDF_MULTITEXTURE))
			//						{
			//							Driver->extGlActiveTexture(GL_TEXTURE1_ARB);
			//#ifdef GL_ARB_texture_env_combine
			//							glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			//									GL_COMBINE_ARB);
			//							glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB,
			//									GL_ADD_SIGNED_ARB);
			//							glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB,
			//									GL_PREVIOUS_ARB);
			//							glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB,
			//									GL_TEXTURE);
			//#else
			//							glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			//									GL_COMBINE_EXT);
			//							glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT,
			//									GL_ADD_SIGNED_EXT);
			//							glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT,
			//									GL_PREVIOUS_EXT);
			//							glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT,
			//									GL_TEXTURE);
			//#endif
			//						}
			//					}
		}

		//! Called by the IVideoDriver to unset this material.
		void COpenGLMaterialRendererDetailMap::OnUnsetMaterial()
		{
			//					if (Driver->queryFeature(EVDF_MULTITEXTURE))
			//					{
			//						Driver->extGlActiveTexture(GL_TEXTURE1_ARB);
			//						glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			//								GL_MODULATE);
			//						Driver->extGlActiveTexture(GL_TEXTURE0_ARB);
			//					}
		}

		IMaterialRenderer* IMaterialRenderer::createMaterialRendererDetailMap(IVideoDriver* driver)
		{
			return new COpenGLMaterialRendererDetailMap(driver);
		}

	} /* namespace video */
} /* namespace irrgame */
