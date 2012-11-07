/*
 * COpenGLMaterialRendererTransparentAlphaChannelRef.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "COpenGLMaterialRendererTransparentAlphaChannelRef.h"

namespace irrgame
{
	namespace video
	{

		//! Default constructor
		COpenGLMaterialRendererTransparentAlphaChannelRef::COpenGLMaterialRendererTransparentAlphaChannelRef(
				IVideoDriver* driver) :
				COpenGLMaterialRenderer(driver)
		{
		}

		//! Destructor
		COpenGLMaterialRendererTransparentAlphaChannelRef::~COpenGLMaterialRendererTransparentAlphaChannelRef()
		{
		}

		//! Called by the IVideoDriver implementation the let the renderer set its needed render states.
		void COpenGLMaterialRendererTransparentAlphaChannelRef::OnSetMaterial(
				const SMaterial& material, const SMaterial& lastMaterial,
				bool resetAllRenderstates, IMaterialRendererServices* services)
		{
			//					Driver->disableTextures(1);
			//					Driver->setBasicRenderStates(material, lastMaterial,
			//							resetAllRenderstates);
			//
			//					if (material.MaterialType != lastMaterial.MaterialType
			//							|| resetAllRenderstates)
			//					{
			//						glEnable (GL_ALPHA_TEST);
			//						glAlphaFunc(GL_GREATER, 0.5f);
			//						glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			//								GL_MODULATE);
			//					}
		}

		//! Called by the IVideoDriver to unset this material.
		/** Called during the IVideoDriver::setMaterial() call before the new
		 material will get the OnSetMaterial() call. */
		void COpenGLMaterialRendererTransparentAlphaChannelRef::OnUnsetMaterial()
		{
			//					glDisable (GL_ALPHA_TEST);
		}

		//! Returns if the material is transparent.
		bool COpenGLMaterialRendererTransparentAlphaChannelRef::isTransparent() const
		{
			return false; // this material is not really transparent because it does no blending.
		}

		IMaterialRenderer* IMaterialRenderer::createMaterialRendererTransparentAlphaChannelRef(IVideoDriver* driver)
		{
			return new COpenGLMaterialRendererTransparentAlphaChannelRef(driver);
		}

	} /* namespace video */
} /* namespace irrgame */
