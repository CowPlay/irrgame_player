/*
 * COpenGLMaterialRendererSolid.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: gregorytkach
 */

#include "COpenGLMaterialRendererSolid.h"

namespace irrgame
{
	namespace video
	{

		//! Default constructor
		COpenGLMaterialRendererSolid::COpenGLMaterialRendererSolid(
				IVideoDriver* driver) :
				COpenGLMaterialRenderer(driver)
		{
		}

		//! Destructor
		COpenGLMaterialRendererSolid::~COpenGLMaterialRendererSolid()
		{

		}

		//FIXME
		//! Called by the IVideoDriver implementation the let the renderer set its needed render states.
		void COpenGLMaterialRendererSolid::OnSetMaterial(
				const SMaterial& material, const SMaterial& lastMaterial,
				bool resetAllRenderstates, IMaterialRendererServices* services)
		{
//			Driver->disableTextures(1);
//			Driver->setBasicRenderStates(material, lastMaterial,
//					resetAllRenderstates);

//			if (resetAllRenderstates
//					|| (material.MaterialType != lastMaterial.MaterialType))
//			{
			// thanks to Murphy, the following line removed some
			// bugs with several OpenGL implementations.
//				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//			}
		}

		IMaterialRenderer* IMaterialRenderer::createMaterialRendererSolid(IVideoDriver* driver)
		{
			return new COpenGLMaterialRendererSolid(driver);
		}

	} /* namespace video */
} /* namespace irrgame */
