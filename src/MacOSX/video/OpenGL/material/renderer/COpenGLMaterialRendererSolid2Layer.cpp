/*
 * COpenGLMaterialRendererSolid2Layer.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "COpenGLMaterialRendererSolid2Layer.h"

namespace irrgame
{
	namespace video
	{

		//! Default constructor
		COpenGLMaterialRendererSolid2Layer::COpenGLMaterialRendererSolid2Layer(
				IVideoDriver* driver) :
				COpenGLMaterialRenderer(driver)
		{
		}

		//! Destructor
		COpenGLMaterialRendererSolid2Layer::~COpenGLMaterialRendererSolid2Layer()
		{
		}

		//! Called by the IVideoDriver implementation the let the renderer set its needed render states.
		void COpenGLMaterialRendererSolid2Layer::OnSetMaterial(
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
//						if (Driver->queryFeature(EVDF_MULTITEXTURE))
//						{
//							Driver->extGlActiveTexture(GL_TEXTURE1_ARB);
//#ifdef GL_ARB_texture_env_combine
//							glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
//									GL_COMBINE_ARB);
//							glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB,
//									GL_REPLACE);
//							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_ARB,
//									GL_PRIMARY_COLOR_ARB);
//							glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB,
//									GL_INTERPOLATE);
//							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB,
//									GL_PREVIOUS_ARB);
//							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB,
//									GL_TEXTURE);
//							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE2_RGB_ARB,
//									GL_PRIMARY_COLOR);
//							glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND2_RGB_ARB,
//									GL_SRC_ALPHA);
//#else
//							glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
//							glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_REPLACE);
//							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT, GL_PRIMARY_COLOR_EXT);
//							glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_INTERPOLATE);
//							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_PREVIOUS_EXT);
//							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_TEXTURE);
//							glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE2_RGB_EXT, GL_PRIMARY_COLOR);
//							glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND2_RGB_EXT, GL_SRC_ALPHA);
//#endif
//						}
//					}
		}

		//! Called by the IVideoDriver to unset this material.
		void COpenGLMaterialRendererSolid2Layer::OnUnsetMaterial()
		{
//					if (Driver->queryFeature(EVDF_MULTITEXTURE))
//					{
//						Driver->extGlActiveTexture(GL_TEXTURE1_ARB);
//						glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
//								GL_MODULATE);
//#ifdef GL_ARB_texture_env_combine
//						glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND2_RGB_ARB,
//								GL_SRC_COLOR);
//#else
//						glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND2_RGB_EXT, GL_SRC_COLOR);
//#endif
//						Driver->extGlActiveTexture(GL_TEXTURE0_ARB);
//					}
		}

	} /* namespace video */
} /* namespace irrgame */
