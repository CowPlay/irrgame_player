/*
 * COpenGLMaterialRendererTransparentAlphaChannel.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "COpenGLMaterialRendererTransparentAlphaChannel.h"

namespace irrgame
{
	namespace video
	{

		//! Default constructor
		COpenGLMaterialRendererTransparentAlphaChannel::COpenGLMaterialRendererTransparentAlphaChannel(
				IVideoDriver* driver) :
				COpenGLMaterialRenderer(driver)
		{
		}

		//! Destructor
		COpenGLMaterialRendererTransparentAlphaChannel::~COpenGLMaterialRendererTransparentAlphaChannel()
		{
		}

		//! Called by the IVideoDriver implementation the let the renderer set its needed render states.
		void COpenGLMaterialRendererTransparentAlphaChannel::OnSetMaterial(
				const SMaterial& material, const SMaterial& lastMaterial,
				bool resetAllRenderstates, IMaterialRendererServices* services)
		{
			//					Driver->disableTextures(1);
			//					Driver->setBasicRenderStates(material, lastMaterial,
			//							resetAllRenderstates);
			//
			//					if (material.MaterialType != lastMaterial.MaterialType
			//							|| resetAllRenderstates
			//							|| material.MaterialTypeParam
			//									!= lastMaterial.MaterialTypeParam)
			//					{
			//#ifdef GL_ARB_texture_env_combine
			//						glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			//								GL_COMBINE_ARB);
			//						glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB,
			//								GL_MODULATE);
			//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB,
			//								GL_TEXTURE);
			//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB,
			//								GL_PREVIOUS_ARB);
			//						glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB,
			//								GL_REPLACE);
			//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_ARB,
			//								GL_TEXTURE);
			//#else
			//						glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
			//						glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_MODULATE);
			//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_TEXTURE);
			//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_PREVIOUS_EXT);
			//						glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_REPLACE);
			//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, GL_TEXTURE);
			//#endif
			//						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//						glEnable(GL_BLEND);
			//						glEnable(GL_ALPHA_TEST);
			//
			//						glAlphaFunc(GL_GREATER, material.MaterialTypeParam);
			//					}
		}

		//! Called by the IVideoDriver to unset this material.
		void COpenGLMaterialRendererTransparentAlphaChannel::OnUnsetMaterial()
		{
			//					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			//#ifdef GL_ARB_texture_env_combine
			//					glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB,
			//							GL_MODULATE);
			//#else
			//					glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_MODULATE );
			//#endif
			//					glDisable(GL_ALPHA_TEST);
			//					glDisable(GL_BLEND);
		}

		//! Returns if the material is transparent.
		bool COpenGLMaterialRendererTransparentAlphaChannel::isTransparent() const
		{
			return true;
		}

	} /* namespace video */
} /* namespace irrgame */
