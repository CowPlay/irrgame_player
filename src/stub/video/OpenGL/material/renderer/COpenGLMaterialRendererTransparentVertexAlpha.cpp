/*
 * COpenGLMaterialRendererTransparentVertexAlpha.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "COpenGLMaterialRendererTransparentVertexAlpha.h"

namespace irrgame
{
	namespace video
	{

		//! Default constructor
		COpenGLMaterialRendererTransparentVertexAlpha::COpenGLMaterialRendererTransparentVertexAlpha(
				IVideoDriver* driver) :
				COpenGLMaterialRenderer(driver)
		{
		}

		//! Destructor
		COpenGLMaterialRendererTransparentVertexAlpha::~COpenGLMaterialRendererTransparentVertexAlpha()
		{
		}

		//FIXME
		//! Called by the IVideoDriver implementation the let the renderer set its needed render states.
		void COpenGLMaterialRendererTransparentVertexAlpha::OnSetMaterial(
				const SMaterial& material, const SMaterial& lastMaterial,
				bool resetAllRenderstates, IMaterialRendererServices* services)
		{
//			Driver->disableTextures(1);
//			Driver->setBasicRenderStates(material, lastMaterial,
//					resetAllRenderstates);
//
//			if (material.MaterialType != lastMaterial.MaterialType
//					|| resetAllRenderstates)
//			{
//#ifdef GL_ARB_texture_env_combine
//				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
//				glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB, GL_REPLACE);
//				glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_ARB,
//						GL_PRIMARY_COLOR_ARB);
//				glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_MODULATE);
//				glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_PREVIOUS_ARB);
//				glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_TEXTURE);
//#else
//				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
//				glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_REPLACE);
//				glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, GL_PRIMARY_COLOR_EXT );
//				glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_MODULATE);
//				glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_PREVIOUS_EXT);
//				glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_TEXTURE);
//#endif
//				glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//				glEnable(GL_BLEND);
//			}
		}

		//FIXME
		//! Called by the IVideoDriver to unset this material.
		void COpenGLMaterialRendererTransparentVertexAlpha::OnUnsetMaterial()
		{
//			// default values
//			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//#ifdef GL_ARB_texture_env_combine
//			glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB, GL_MODULATE);
//			glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_ARB, GL_TEXTURE);
//#else
//			glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_MODULATE );
//			glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, GL_TEXTURE );
//#endif
//			glDisable(GL_BLEND);
		}

		//! Returns if the material is transparent.
		bool COpenGLMaterialRendererTransparentVertexAlpha::isTransparent() const
		{
			return true;
		}

	} /* namespace video */
} /* namespace irrgame */
