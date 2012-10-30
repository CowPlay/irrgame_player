/*
 * COpenGLMaterialRendererReflection2Layer.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "COpenGLMaterialRendererReflection2Layer.h"

namespace irrgame
{
	namespace video
	{
		//! Default constructor
		COpenGLMaterialRendererReflection2Layer::COpenGLMaterialRendererReflection2Layer(
				IVideoDriver* driver) :
				COpenGLMaterialRenderer(driver)
		{
		}

		//! Destructor
		COpenGLMaterialRendererReflection2Layer::~COpenGLMaterialRendererReflection2Layer()
		{
		}

		//FIXME
		//! Called by the IVideoDriver implementation the let the renderer set its needed render states.
		void COpenGLMaterialRendererReflection2Layer::OnSetMaterial(
				const SMaterial& material, const SMaterial& lastMaterial,
				bool resetAllRenderstates, IMaterialRendererServices* services)
		{
//			Driver->disableTextures(2);
//			Driver->setBasicRenderStates(material, lastMaterial,
//					resetAllRenderstates);
//
//			if (material.MaterialType != lastMaterial.MaterialType
//					|| resetAllRenderstates)
//			{
//				if (Driver->queryFeature(EVDF_MULTITEXTURE))
//				{
//					Driver->extGlActiveTexture(GL_TEXTURE1_ARB);
//#ifdef GL_ARB_texture_env_combine
//					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
//							GL_COMBINE_ARB);
//					glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB,
//							GL_MODULATE);
//					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB,
//							GL_PREVIOUS_ARB);
//					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB,
//							GL_TEXTURE);
//#else
//					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
//							GL_COMBINE_EXT);
//					glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_MODULATE);
//					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT,
//							GL_PREVIOUS_EXT);
//					glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_TEXTURE);
//#endif
//				}
//				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
//				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
//				glEnable (GL_TEXTURE_GEN_S);
//				glEnable (GL_TEXTURE_GEN_T);
//			}
		}

		//FIXME
		//! Called by the IVideoDriver to unset this material.
		void COpenGLMaterialRendererReflection2Layer::OnUnsetMaterial()
		{
//			if (Driver->queryFeature(EVDF_MULTITEXTURE))
//			{
//				Driver->extGlActiveTexture(GL_TEXTURE1_ARB);
//				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//			}
//			glDisable (GL_TEXTURE_GEN_S);
//			glDisable (GL_TEXTURE_GEN_T);
//			if (Driver->queryFeature(EVDF_MULTITEXTURE))
//			{
//				Driver->extGlActiveTexture(GL_TEXTURE0_ARB);
//			}
		}

	} /* namespace video */
} /* namespace irrgame */
