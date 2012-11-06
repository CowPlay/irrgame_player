/*
 * COpenGLMaterialRendererTransparentAddColor.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "COpenGLMaterialRendererTransparentAddColor.h"

namespace irrgame
{
	namespace video
	{

		//! Default constructor
		COpenGLMaterialRendererTransparentAddColor::COpenGLMaterialRendererTransparentAddColor(
				IVideoDriver* driver) :
				COpenGLMaterialRenderer(driver)
		{
		}

		//! Destructor
		COpenGLMaterialRendererTransparentAddColor::~COpenGLMaterialRendererTransparentAddColor()
		{
		}

		//! Called by the IVideoDriver implementation the let the renderer set its needed render states.
		void COpenGLMaterialRendererTransparentAddColor::OnSetMaterial(
				const SMaterial& material, const SMaterial& lastMaterial,
				bool resetAllRenderstates, IMaterialRendererServices* services)
		{
//			Driver->disableTextures(1);
//			Driver->setBasicRenderStates(material, lastMaterial,
//					resetAllRenderstates);
//
//			if ((material.MaterialType != lastMaterial.MaterialType)
//					|| resetAllRenderstates)
//			{
//				glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
//				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//				glEnable(GL_BLEND);
//			}
		}

		//! Called by the IVideoDriver to unset this material.
		void COpenGLMaterialRendererTransparentAddColor::OnUnsetMaterial()
		{
//			glDisable(GL_BLEND);
		}

		//! Returns if the material is transparent.
		bool COpenGLMaterialRendererTransparentAddColor::isTransparent() const
		{
			return true;
		}

	} /* namespace video */
} /* namespace irrgame */
