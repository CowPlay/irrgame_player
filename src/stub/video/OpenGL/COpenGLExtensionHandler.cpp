// Copyright (C) 2002-2010 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "COpenGLExtensionHandler.h"

#include "core/irrgamemath.h"

namespace irrgame
{
	namespace video
	{

		//! Singleton realization
		IOpenGLExtensionHandler& IOpenGLExtensionHandler::getInstance()
		{
			static COpenGLExtensionHandler instance;
			return instance;
		}

		COpenGLExtensionHandler::COpenGLExtensionHandler() :
				IOpenGLExtensionHandler()
		{
		}

		void COpenGLExtensionHandler::dump() const
		{
			for (u32 i = 0; i < IRR_OpenGL_Feature_Count; ++i)
			{

				//TODO: refactor it
				//os::Printer::log(OpenGLFeatureStrings[i], FeatureAvailable[i] ? " true" : " false");
			}
		}



		void COpenGLExtensionHandler::initExtensions(bool stencilBuffer)
		{
			const f32 ogl_ver = core::fast_atof(
					reinterpret_cast<const c8*>(glGetString(GL_VERSION)));
			Version = static_cast<u16>(core::floor32(ogl_ver) * 100
					+ core::round32(core::fract(ogl_ver) * 10.0f));

			//TODO: refactor it
			//if (Version >= 102)
			//os::Printer::log("OpenGL driver version is 1.2 or better.",	ELL_INFORMATION);
			//else
			//os::Printer::log("OpenGL driver version is not 1.2 or better.", ELL_WARNING);

			{
				const char* t = reinterpret_cast<const char*>(glGetString(
						GL_EXTENSIONS));
				size_t len = 0;
				c8 *str = 0;
				if (t)
				{
					len = strlen(t);
					str = new c8[len + 1];
				}
				c8* p = str;

				for (size_t i = 0; i < len; ++i)
				{
					str[i] = static_cast<char>(t[i]);

					if (str[i] == ' ')
					{
						str[i] = 0;
						for (u32 j = 0; j < IRR_OpenGL_Feature_Count; ++j)
						{
							if (!strcmp(OpenGLFeatureStrings[j], p))
							{
								FeatureAvailable[j] = true;
								break;
							}
						}

						p = p + strlen(p) + 1;
					}
				}

				delete[] str;
			}

			MultiTextureExtension = FeatureAvailable[IRR_ARB_multitexture];
			TextureCompressionExtension =
					FeatureAvailable[IRR_ARB_texture_compression];
			StencilBuffer = stencilBuffer;

			GLint num;
			// set some properties
#if defined(GL_ARB_multitexture) || defined(GL_VERSION_1_3)
			if (Version > 102 || FeatureAvailable[IRR_ARB_multitexture])
			{
				glGetIntegerv(GL_MAX_TEXTURE_UNITS, &num);
				MaxTextureUnits = static_cast<u8>(num);
			}
#endif
			glGetIntegerv(GL_MAX_LIGHTS, &num);
			MaxLights = static_cast<u8>(num);
#ifdef GL_EXT_texture_filter_anisotropic
			if (FeatureAvailable[IRR_EXT_texture_filter_anisotropic])
			{
				glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &num);
				MaxAnisotropy = static_cast<u8>(num);
			}
#endif
#ifdef GL_VERSION_1_2
			if (Version > 101)
			{
				glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &num);
				MaxIndices = num;
			}
#endif
			glGetIntegerv(GL_MAX_TEXTURE_SIZE, &num);
			MaxTextureSize = static_cast<u32>(num);
			if (queryFeature(EVDF_GEOMETRY_SHADER))
			{
#if defined(GL_ARB_geometry_shader4) || defined(GL_EXT_geometry_shader4) || defined(GL_NV_geometry_shader4)
				glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT, &num);
				MaxGeometryVerticesOut = static_cast<u32>(num);
#endif
			}
#ifdef GL_EXT_texture_lod_bias
			if (FeatureAvailable[IRR_EXT_texture_lod_bias])
				glGetFloatv(GL_MAX_TEXTURE_LOD_BIAS_EXT, &MaxTextureLODBias);
#endif
			glGetIntegerv(GL_MAX_CLIP_PLANES, &num);
			MaxUserClipPlanes = static_cast<u8>(num);
			glGetIntegerv(GL_AUX_BUFFERS, &num);
			MaxAuxBuffers = static_cast<u8>(num);

#ifdef GL_ARB_draw_buffers
			if (FeatureAvailable[IRR_ARB_draw_buffers])
			{
				glGetIntegerv(GL_MAX_DRAW_BUFFERS_ARB, &num);
				MaxMultipleRenderTargets = static_cast<u8>(num);
			}
#endif
			glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, DimAliasedLine);
			glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, DimAliasedPoint);
			glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, DimSmoothedLine);
			glGetFloatv(GL_SMOOTH_POINT_SIZE_RANGE, DimSmoothedPoint);
#if defined(GL_ARB_shading_language_100) || defined (GL_VERSION_2_0)
			if (FeatureAvailable[IRR_ARB_shading_language_100]
					|| Version >= 200)
			{
				glGetError(); // clean error buffer
#ifdef GL_SHADING_LANGUAGE_VERSION
				const GLubyte* shaderVersion = glGetString(
						GL_SHADING_LANGUAGE_VERSION);
#else
				const GLubyte* shaderVersion = glGetString(GL_SHADING_LANGUAGE_VERSION_ARB);
#endif
				if (glGetError() == GL_INVALID_ENUM)
					ShaderLanguageVersion = 100;
				else
				{
					const f32 sl_ver = core::fast_atof(
							reinterpret_cast<const c8*>(shaderVersion));
					ShaderLanguageVersion = static_cast<u16>(core::floor32(
							sl_ver) * 100
							+ core::round32(core::fract(sl_ver) * 10.0f));
				}
			}
#endif

			if (MaxTextureUnits < 2)
			{
				MultiTextureExtension = false;
				//os::Printer::log("Warning: OpenGL device only has one texture unit. Disabling multitexturing.", ELL_WARNING);
			}
			MaxTextureUnits = core::min_(MaxTextureUnits,
					static_cast<u8>(MaterialMaxTextures));

		}

		bool COpenGLExtensionHandler::queryFeature(
				EVideoDriverFeatures feature) const
		{
			switch (feature)
			{
				case EVDF_RENDER_TO_TARGET:
				{
					return true;
				}
				case EVDF_HARDWARE_TL:
				{
					return true; // we cannot tell other things
				}
				case EVDF_MULTITEXTURE:
					return MultiTextureExtension;
				case EVDF_BILINEAR_FILTER:
					return true;
				case EVDF_MIP_MAP:
					return true;
				case EVDF_MIP_MAP_AUTO_UPDATE:
					return FeatureAvailable[IRR_SGIS_generate_mipmap];
				case EVDF_STENCIL_BUFFER:
					return StencilBuffer;
				case EVDF_VERTEX_SHADER_1_1:
				case EVDF_ARB_VERTEX_PROGRAM_1:
					return FeatureAvailable[IRR_ARB_vertex_program]
							|| FeatureAvailable[IRR_NV_vertex_program1_1];
				case EVDF_PIXEL_SHADER_1_1:
				case EVDF_PIXEL_SHADER_1_2:
				case EVDF_ARB_FRAGMENT_PROGRAM_1:
					return FeatureAvailable[IRR_ARB_fragment_program]
							|| FeatureAvailable[IRR_NV_fragment_program];
				case EVDF_PIXEL_SHADER_2_0:
				case EVDF_VERTEX_SHADER_2_0:
				case EVDF_ARB_GLSL:
					return (FeatureAvailable[IRR_ARB_shading_language_100]
							|| Version >= 200);
				case EVDF_TEXTURE_NSQUARE:
					return true; // non-square is always supported
				case EVDF_TEXTURE_NPOT:
					// Some ATI cards seem to have only SW support in OpenGL 2.0
					// drivers if the extension is not exposed, so we skip this
					// extra test for now!
					// return (FeatureAvailable[IRR_ARB_texture_non_power_of_two]||Version>=200);
					return (FeatureAvailable[IRR_ARB_texture_non_power_of_two]);
				case EVDF_FRAMEBUFFER_OBJECT:
					return FeatureAvailable[IRR_EXT_framebuffer_object];
				case EVDF_VERTEX_BUFFER_OBJECT:
					return FeatureAvailable[IRR_ARB_vertex_buffer_object];
				case EVDF_COLOR_MASK:
					return true;
				case EVDF_ALPHA_TO_COVERAGE:
					return FeatureAvailable[IRR_ARB_multisample];
				case EVDF_GEOMETRY_SHADER:
					return FeatureAvailable[IRR_ARB_geometry_shader4]
							|| FeatureAvailable[IRR_EXT_geometry_shader4]
							|| FeatureAvailable[IRR_NV_geometry_program4]
							|| FeatureAvailable[IRR_NV_geometry_shader4];
				case EVDF_MULTIPLE_RENDER_TARGETS:
					return FeatureAvailable[IRR_ARB_draw_buffers]
							|| FeatureAvailable[IRR_ATI_draw_buffers];
				case EVDF_MRT_BLEND:
				case EVDF_MRT_COLOR_MASK:
					return FeatureAvailable[IRR_EXT_draw_buffers2];
				case EVDF_MRT_BLEND_FUNC:
					return FeatureAvailable[IRR_ARB_draw_buffers_blend]
							|| FeatureAvailable[IRR_AMD_draw_buffers_blend];
				default:
					return false;
			};
		}

	}
}
