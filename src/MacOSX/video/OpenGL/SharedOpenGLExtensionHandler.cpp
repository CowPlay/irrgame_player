// Copyright (C) 2002-2010 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "SharedOpenGLExtensionHandler.h"

#include "core/irrgamemath.h"

namespace irrgame
{
	namespace video
	{

		//! Singleton realization
		SharedOpenGLExtensionHandler& SharedOpenGLExtensionHandler::getInstance()
		{
			static SharedOpenGLExtensionHandler instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		SharedOpenGLExtensionHandler::SharedOpenGLExtensionHandler() :
				StencilBuffer(false), MultiTextureExtension(false), TextureCompressionExtension(
						false), MaxTextureUnits(1), MaxLights(1), MaxAnisotropy(
						1), MaxUserClipPlanes(0), MaxAuxBuffers(0), MaxMultipleRenderTargets(
						1), MaxIndices(65535), MaxTextureSize(1), MaxGeometryVerticesOut(
						0), MaxTextureLODBias(0.f), Version(0), ShaderLanguageVersion(
						0)
		{
			for (u32 i = 0; i < IRR_OpenGL_Feature_Count; ++i)
				FeatureAvailable[i] = false;

			DimAliasedLine[0] = 1.f;
			DimAliasedLine[1] = 1.f;
			DimAliasedPoint[0] = 1.f;
			DimAliasedPoint[1] = 1.f;
			DimSmoothedLine[0] = 1.f;
			DimSmoothedLine[1] = 1.f;
			DimSmoothedPoint[0] = 1.f;
			DimSmoothedPoint[1] = 1.f;
		}

		//! Destructor. Should use only one time.
		SharedOpenGLExtensionHandler::~SharedOpenGLExtensionHandler()
		{
		}

		void SharedOpenGLExtensionHandler::dump() const
		{
			for (u32 i = 0; i < IRR_OpenGL_Feature_Count; ++i)
			{
				//TODO: refactor it
				//os::Printer::log(OpenGLFeatureStrings[i], FeatureAvailable[i] ? " true" : " false");
			}
		}

		// deferred initialization
		void SharedOpenGLExtensionHandler::initExtensions(bool stencilBuffer)
		{
			const f32 ogl_ver =
					core::SharedConverter::getInstance().convertToFloat(
							reinterpret_cast<const c8*>(glGetString(GL_VERSION)));
			Version =
					static_cast<u16>(core::SharedFastMath::getInstance().floor32(
							ogl_ver) * 100
							+ core::SharedFastMath::getInstance().round32(
									core::SharedMath::getInstance().fract(
											ogl_ver) * 10.0f));

			//TODO: check version OpenGL and tell to customer about wrong version
			IRR_ASSERT(Version >= 200);

			const c8* t = reinterpret_cast<const char*>(glGetString(
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

			MultiTextureExtension = FeatureAvailable[IRR_ARB_multitexture];
			TextureCompressionExtension =
					FeatureAvailable[IRR_ARB_texture_compression];
			StencilBuffer = stencilBuffer;

			GLint num;
			// set some properties
			if (Version > 102 || FeatureAvailable[IRR_ARB_multitexture])
			{
				glGetIntegerv(GL_MAX_TEXTURE_UNITS, &num);
				MaxTextureUnits = static_cast<u8>(num);
			}

			glGetIntegerv(GL_MAX_LIGHTS, &num);
			MaxLights = static_cast<u8>(num);
			if (FeatureAvailable[IRR_EXT_texture_filter_anisotropic])
			{
				glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &num);
				MaxAnisotropy = static_cast<u8>(num);
			}

			if (Version > 101)
			{
				glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &num);
				MaxIndices = num;
			}

			glGetIntegerv(GL_MAX_TEXTURE_SIZE, &num);
			MaxTextureSize = static_cast<u32>(num);
			if (queryFeature(EVDF_GEOMETRY_SHADER))
			{

				glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT, &num);
				MaxGeometryVerticesOut = static_cast<u32>(num);

			}

			if (FeatureAvailable[IRR_EXT_texture_lod_bias])
			{
				glGetFloatv(GL_MAX_TEXTURE_LOD_BIAS_EXT, &MaxTextureLODBias);
			}
			glGetIntegerv(GL_MAX_CLIP_PLANES, &num);
			MaxUserClipPlanes = static_cast<u8>(num);
			glGetIntegerv(GL_AUX_BUFFERS, &num);
			MaxAuxBuffers = static_cast<u8>(num);

			if (FeatureAvailable[IRR_ARB_draw_buffers])
			{
				glGetIntegerv(GL_MAX_DRAW_BUFFERS_ARB, &num);
				MaxMultipleRenderTargets = static_cast<u8>(num);
			}

			glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, DimAliasedLine);
			glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, DimAliasedPoint);
			glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, DimSmoothedLine);
			glGetFloatv(GL_SMOOTH_POINT_SIZE_RANGE, DimSmoothedPoint);

			if (FeatureAvailable[IRR_ARB_shading_language_100]
					|| Version >= 200)
			{
				glGetError(); // clean error buffer
				const GLubyte* shaderVersion = glGetString(
						GL_SHADING_LANGUAGE_VERSION);
				if (glGetError() == GL_INVALID_ENUM)
					ShaderLanguageVersion = 100;
				else
				{
					const f32 sl_ver =
							core::SharedConverter::getInstance().convertToFloat(
									reinterpret_cast<const c8*>(shaderVersion));
					ShaderLanguageVersion =
							static_cast<u16>(core::SharedFastMath::getInstance().floor32(
									sl_ver) * 100
									+ core::SharedFastMath::getInstance().round32(
											core::SharedMath::getInstance().fract(
													sl_ver) * 10.0f));
				}
			}

			if (MaxTextureUnits < 2)
			{
				MultiTextureExtension = false;
				//os::Printer::log("Warning: OpenGL device only has one texture unit. Disabling multitexturing.", ELL_WARNING);
			}
			MaxTextureUnits = core::SharedMath::getInstance().min(
					MaxTextureUnits, static_cast<u8>(MaterialMaxTextures));

		}

		//! Checking if video driver suppports feature (OpenGL have default always supported features what can be returned as true)
		bool SharedOpenGLExtensionHandler::queryFeature(
				EVideoDriverFeatures feature) const
		{
			bool result = false;

			switch (feature)
			{
				case EVDF_RENDER_TO_TARGET:
				{
					result = true;
					break;
				}
				case EVDF_HARDWARE_TL:
				{
					result = true; // we cannot tell other things
					break;
				}
				case EVDF_MULTITEXTURE:
				{
					result = MultiTextureExtension;
					break;
				}
				case EVDF_BILINEAR_FILTER:
				{
					result = true;
					break;
				}
				case EVDF_MIP_MAP:
				{
					result = true;
					break;
				}
				case EVDF_MIP_MAP_AUTO_UPDATE:
				{
					result = FeatureAvailable[IRR_SGIS_generate_mipmap];
					break;
				}
				case EVDF_STENCIL_BUFFER:
				{
					result = StencilBuffer;
					break;
				}
				case EVDF_VERTEX_SHADER_1_1:
				case EVDF_ARB_VERTEX_PROGRAM_1:
				{
					result = FeatureAvailable[IRR_ARB_vertex_program]
							|| FeatureAvailable[IRR_NV_vertex_program1_1];
					break;
				}
				case EVDF_PIXEL_SHADER_1_1:
				case EVDF_PIXEL_SHADER_1_2:
				case EVDF_ARB_FRAGMENT_PROGRAM_1:
				{
					result = FeatureAvailable[IRR_ARB_fragment_program]
							|| FeatureAvailable[IRR_NV_fragment_program];
					break;
				}
				case EVDF_PIXEL_SHADER_2_0:
				case EVDF_VERTEX_SHADER_2_0:
				case EVDF_ARB_GLSL:
				{
					result = (FeatureAvailable[IRR_ARB_shading_language_100]
							|| Version >= 200);
					break;
				}
				case EVDF_TEXTURE_NSQUARE:
				{
					// non-square is always supported
					result = true;
					break;
				}
				case EVDF_TEXTURE_NPOT:
				{
					// Some ATI cards seem to have only SW support in OpenGL 2.0
					// drivers if the extension is not exposed, so we skip this
					// extra test for now!
					// return (FeatureAvailable[IRR_ARB_texture_non_power_of_two]||Version>=200);
					result =
							(FeatureAvailable[IRR_ARB_texture_non_power_of_two]);
					break;
				}
				case EVDF_FRAMEBUFFER_OBJECT:
				{
					result = FeatureAvailable[IRR_EXT_framebuffer_object];
					break;
				}
				case EVDF_VERTEX_BUFFER_OBJECT:
				{
					result = FeatureAvailable[IRR_ARB_vertex_buffer_object];
					break;
				}
				case EVDF_COLOR_MASK:
				{
					result = true;
					break;
				}
				case EVDF_ALPHA_TO_COVERAGE:
				{
					result = FeatureAvailable[IRR_ARB_multisample];
					break;
				}
				case EVDF_GEOMETRY_SHADER:
				{
					result = FeatureAvailable[IRR_ARB_geometry_shader4]
							|| FeatureAvailable[IRR_EXT_geometry_shader4]
							|| FeatureAvailable[IRR_NV_geometry_program4]
							|| FeatureAvailable[IRR_NV_geometry_shader4];
					break;
				}
				case EVDF_MULTIPLE_RENDER_TARGETS:
				{
					result = FeatureAvailable[IRR_ARB_draw_buffers]
							|| FeatureAvailable[IRR_ATI_draw_buffers];
					break;
				}
				case EVDF_MRT_BLEND:
				case EVDF_MRT_COLOR_MASK:
				{
					result = FeatureAvailable[IRR_EXT_draw_buffers2];
					break;
				}
				case EVDF_MRT_BLEND_FUNC:
				{
					result = FeatureAvailable[IRR_ARB_draw_buffers_blend]
							|| FeatureAvailable[IRR_AMD_draw_buffers_blend];
					break;
				}
				default:
				{
					// To prevent sending trash on development stage
					IRR_ASSERT(false);
					break;
				}
			};

			return result;
		}

		//! queries the features of the driver, returns true if feature is available
		bool SharedOpenGLExtensionHandler::isOpenGLFeatureAvailable(
				EOpenGLFeatures feature) const
		{
			return FeatureAvailable[feature];
		}

		//! Selecting current texture coordinate set for texture mapping
		inline void SharedOpenGLExtensionHandler::extGlActiveTexture(
				GLenum texture)
		{
			if (MultiTextureExtension)
			{
				glActiveTextureARB(texture);
			}
		}

	} //namespace video
} //namespace irrgame
