/*
 * COpenGLMaterialRendererSphereMap.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "COpenGLMaterialRendererSphereMap.h"

namespace irrgame
{
	namespace video
	{
		//! Default constructor
		COpenGLMaterialRendererSphereMap::COpenGLMaterialRendererSphereMap(
				IVideoDriver* driver) :
				COpenGLMaterialRenderer(driver)
		{
		}

		//! Destructor
		COpenGLMaterialRendererSphereMap::~COpenGLMaterialRendererSphereMap()
		{
		}

		//FIXME
		//! Called by the IVideoDriver implementation the let the renderer set its needed render states.
		void COpenGLMaterialRendererSphereMap::OnSetMaterial(
				const SMaterial& material, const SMaterial& lastMaterial,
				bool resetAllRenderstates, IMaterialRendererServices* services)
		{
//			Driver->disableTextures(1);
//			// texture needs to be flipped for OpenGL
//			core::matrix4 tmp = Driver->getTransform(ETS_TEXTURE_0);
//			tmp[5] *= -1;
//			Driver->setTransform(ETS_TEXTURE_0, tmp);
//			Driver->setBasicRenderStates(material, lastMaterial,
//					resetAllRenderstates);
//
//			if (material.MaterialType != lastMaterial.MaterialType
//					|| resetAllRenderstates)
//			{
//				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
//				glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
//
//				glEnable (GL_TEXTURE_GEN_S);
//				glEnable (GL_TEXTURE_GEN_T);
//			}
		}

		//FIXME
		//! Called by the IVideoDriver to unset this material.
		void COpenGLMaterialRendererSphereMap::OnUnsetMaterial()
		{
//			glDisable (GL_TEXTURE_GEN_S);
//			glDisable (GL_TEXTURE_GEN_T);
		}

		IMaterialRenderer* IMaterialRenderer::createMaterialRendererSphereMap(IVideoDriver* driver)
		{
			return new COpenGLMaterialRendererSphereMap(driver);
		}
	} /* namespace video */
} /* namespace irrgame */
