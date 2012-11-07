/*
 * COpenGLMaterialRendererOneTextureBlend.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "COpenGLMaterialRendererOneTextureBlend.h"

namespace irrgame
{
	namespace video
	{

		//! Default constructor
		COpenGLMaterialRendererOneTextureBlend::COpenGLMaterialRendererOneTextureBlend(
				IVideoDriver* driver) :
				COpenGLMaterialRenderer(driver)
		{
		}

		//! Destructor
		COpenGLMaterialRendererOneTextureBlend::~COpenGLMaterialRendererOneTextureBlend()
		{
		}

		//FIXME
		//! Called by the IVideoDriver implementation the let the renderer set its needed render states.
		void COpenGLMaterialRendererOneTextureBlend::OnSetMaterial(
				const SMaterial& material, const SMaterial& lastMaterial,
				bool resetAllRenderstates, IMaterialRendererServices* services)
		{
//			Driver->disableTextures(1);
//			Driver->setBasicRenderStates(material, lastMaterial,
//					resetAllRenderstates);

			//		if (material.MaterialType != lastMaterial.MaterialType ||
			//			material.MaterialTypeParam != lastMaterial.MaterialTypeParam ||
			//			resetAllRenderstates)
//			{
//				E_BLEND_FACTOR srcFact, dstFact;
//				E_MODULATE_FUNC modulate;
//				u32 alphaSource;
//				unpack_texureBlendFunc(srcFact, dstFact, modulate, alphaSource,
//						material.MaterialTypeParam);
//
//#ifdef GL_ARB_texture_env_combine
//				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
//				glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_ARB, GL_MODULATE);
//				glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_ARB, GL_TEXTURE);
//				glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_PREVIOUS_ARB);
//				glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, (f32) modulate);
//#else
//				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
//				glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_MODULATE);
//				glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_TEXTURE);
//				glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_PREVIOUS_EXT);
//				glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, (f32) modulate);
//#endif
//
//				glBlendFunc(getGLBlend(srcFact), getGLBlend(dstFact));
//				glEnable(GL_ALPHA_TEST);
//				glAlphaFunc(GL_GREATER, 0.f);
//				glEnable(GL_BLEND);
//
//				if (textureBlendFunc_hasAlpha(srcFact)
//						|| textureBlendFunc_hasAlpha(dstFact))
//				{
//					if (alphaSource == EAS_VERTEX_COLOR)
//					{
//#ifdef GL_ARB_texture_env_combine
//						glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB,
//								GL_REPLACE);
//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_ARB,
//								GL_PRIMARY_COLOR_ARB);
//#else
//						glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT,
//								GL_REPLACE);
//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT,
//								GL_PRIMARY_COLOR_EXT);
//#endif
//					}
//					else if (alphaSource == EAS_TEXTURE)
//					{
//#ifdef GL_ARB_texture_env_combine
//						glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB,
//								GL_REPLACE);
//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_ARB,
//								GL_TEXTURE);
//#else
//						glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT,
//								GL_REPLACE);
//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT,
//								GL_TEXTURE);
//#endif
//					}
//					else
//					{
//#ifdef GL_ARB_texture_env_combine
//						glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB,
//								GL_MODULATE);
//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_ARB,
//								GL_TEXTURE);
//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_ARB,
//								GL_PRIMARY_COLOR_ARB);
//#else
//						glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT,
//								GL_MODULATE);
//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA_EXT,
//								GL_TEXTURE);
//						glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA_EXT,
//								GL_PRIMARY_COLOR_EXT);
//#endif
//					}
//
//#ifdef GL_ARB_texture_env_combine
//					glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB,
//							GL_PRIMARY_COLOR_ARB);
//#else
//					glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT,
//							GL_PRIMARY_COLOR_EXT);
//#endif
//				}
//			}
		}

		//! Called by the IVideoDriver to unset this material.
		void COpenGLMaterialRendererOneTextureBlend::OnUnsetMaterial()
		{
//			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//#ifdef GL_ARB_texture_env_combine
//			glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_ARB, GL_MODULATE);
//			glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 1.f);
//			glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_ARB, GL_PREVIOUS_ARB);
//#else
//			glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_ALPHA_EXT, GL_MODULATE);
//			glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 1.f);
//			glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_PREVIOUS_EXT);
//#endif
//
//			glDisable(GL_BLEND);
//			glDisable(GL_ALPHA_TEST);
		}

		//! Returns if the material is transparent.
		bool COpenGLMaterialRendererOneTextureBlend::isTransparent() const
		{
			return true;
		}

		u32 COpenGLMaterialRendererOneTextureBlend::getGLBlend(
				E_BLEND_FACTOR factor) const
		{
			u32 result = 0;

			switch (factor)
			{
				case EBF_ZERO:
				{
					result = GL_ZERO;
					break;
				}
				case EBF_ONE:
				{
					result = GL_ONE;
					break;
				}
				case EBF_DST_COLOR:
				{
					result = GL_DST_COLOR;
					break;
				}
				case EBF_ONE_MINUS_DST_COLOR:
				{
					result = GL_ONE_MINUS_DST_COLOR;
					break;
				}
				case EBF_SRC_COLOR:
				{
					result = GL_SRC_COLOR;
					break;
				}
				case EBF_ONE_MINUS_SRC_COLOR:
				{
					result = GL_ONE_MINUS_SRC_COLOR;
					break;
				}
				case EBF_SRC_ALPHA:
				{
					result = GL_SRC_ALPHA;
					break;
				}
				case EBF_ONE_MINUS_SRC_ALPHA:
				{
					result = GL_ONE_MINUS_SRC_ALPHA;
					break;
				}
				case EBF_DST_ALPHA:
				{
					result = GL_DST_ALPHA;
					break;
				}
				case EBF_ONE_MINUS_DST_ALPHA:
				{
					result = GL_ONE_MINUS_DST_ALPHA;
					break;
				}
				case EBF_SRC_ALPHA_SATURATE:
				{
					result = GL_SRC_ALPHA_SATURATE;
					break;
				}
				default:
				{
					//Not implemented
					IRR_ASSERT(false);
					break;
				}
			}

			return result;
		}

		IMaterialRenderer* IMaterialRenderer::createMaterialRendererOneTextureBlend(IVideoDriver* driver)
		{
			return new COpenGLMaterialRendererOneTextureBlend(driver);
		}
	}/* namespace video */
}/* namespace irrgame */

