/*
 * COpenGLTexture.cpp
 *
 *  Created on: Oct 16, 2012
 *      Author: gregorytkach
 */

#include "COpenGLTexture.h"
#include "video/image/CImage.h"
#include "SharedOpenGLExtensionHandler.h"

namespace irrgame
{
	namespace video
	{

		//! Default constructor
//		COpenGLTexture::COpenGLTexture(const core::stringc& path) :
//				ITexture(path), IsRenderTarget(false)
//		{
//		}

		//! constructor for usual textures
		COpenGLTexture::COpenGLTexture(IImage* origImage,
				const core::stringc& name, void* mipmapData,
				IVideoDriver* driver) :
				ITexture(name), ColorFormat(ECF_R8G8B8), Driver(
						static_cast<COpenGLDriver *>(driver)), Image(0), MipImage(
						0), TextureName(0), InternalFormat(GL_RGBA), PixelFormat(
						GL_BGRA_EXT), PixelType(GL_UNSIGNED_BYTE), IsRenderTarget(
						false)
		//FIXME
		//AutomaticMipmapUpdate(false),
		//ReadOnlyLock(false),
		//KeepImage(true)
		{

			//TODO: refactor it
			//HasMipMaps = Driver->getTextureCreationFlag(ETCF_CREATE_MIP_MAPS);
			getImageValues(origImage);

			glGenTextures(1, &TextureName);

			if (ImageSize == TextureSize)
			{
				Image = new CImage(ColorFormat, ImageSize);
				origImage->copyTo(Image);
			}
			else
			{
				Image = new CImage(ColorFormat, TextureSize);
				// scale texture
				origImage->copyToScaling(Image);
			}

			uploadTexture(true, mipmapData);

			//FIXME
//			if (!KeepImage)
//			{
//				Image->drop();
//				Image = 0;
//			}
		}

		//! Destructor
		COpenGLTexture::~COpenGLTexture()
		{
		}

		bool COpenGLTexture::isRenderTarget() const
		{
			return IsRenderTarget;
		}

		// prepare values ImageSize, TextureSize, and ColorFormat based on image
		void COpenGLTexture::getImageValues(IImage* image)
		{
			IRR_ASSERT(image);

			ImageSize = image->getDimension();

			IRR_ASSERT(ImageSize.Width && ImageSize.Height);

			const f32 ratio = (f32) ImageSize.Width / (f32) ImageSize.Height;

			if ((ImageSize.Width > Driver->getMaxTextureSize().Width)
					&& (ratio >= 1.0f))
			{
				ImageSize.Width = Driver->getMaxTextureSize().Width;
				ImageSize.Height = (u32) (Driver->getMaxTextureSize().Height
						/ ratio);
			}
			else if (ImageSize.Height > Driver->getMaxTextureSize().Height)
			{
				ImageSize.Height = Driver->getMaxTextureSize().Height;
				ImageSize.Width = (u32) (Driver->getMaxTextureSize().Width
						* ratio);
			}

			TextureSize = ImageSize.getOptimalSize(
					!SharedOpenGLExtensionHandler::getInstance().queryFeature(
							EVDF_TEXTURE_NPOT));

			ColorFormat = getBestColorFormat(image->getColorFormat());

		}

		//FIXME: uncomment and fix method getTextureCreationFlag
		//! Choose best matching color format, bagetTextureCreationFlagsed on texture creation flags
		EColorFormat COpenGLTexture::getBestColorFormat(EColorFormat format)
		{
			EColorFormat destFormat = ECF_A8R8G8B8;

			switch (format)
			{
				case ECF_A1R5G5B5:
//		      if (!Driver->getTextureCreationFlag(ETCF_ALWAYS_32_BIT))
					destFormat = ECF_A1R5G5B5;
					break;
				case ECF_R5G6B5:
//		      if (!Driver->getTextureCreationFlag(ETCF_ALWAYS_32_BIT))
					destFormat = ECF_A1R5G5B5;
					break;
				case ECF_A8R8G8B8:
//		      if (Driver->getTextureCreationFlag(ETCF_ALWAYS_16_BIT) ||
//		          Driver->getTextureCreationFlag(ETCF_OPTIMIZED_FOR_SPEED))
					destFormat = ECF_A1R5G5B5;
					break;
				case ECF_R8G8B8:
//		      if (Driver->getTextureCreationFlag(ETCF_ALWAYS_16_BIT) ||
//		          Driver->getTextureCreationFlag(ETCF_OPTIMIZED_FOR_SPEED))
//					destFormat = ECF_A1R5G5B5;
				default:
					break;
			}

			//FIXME: refactor it
			if (false)//(Driver->getTextureCreationFlag(ETCF_NO_ALPHA_CHANNEL))
			{
				switch (destFormat)
				{
					case ECF_A1R5G5B5:
					{
						destFormat = ECF_R5G6B5;
						break;
					}
					case ECF_A8R8G8B8:
					{
						destFormat = ECF_R8G8B8;
						break;
					}
					default:
					{
						break;
					}
				}
			}

			return destFormat;
		}

		//! Returns size of the original image.
		const dimension2du& COpenGLTexture::getOriginalSize() const
		{
			return ImageSize;
		}

		//! Returns size of the texture.
		const dimension2du& COpenGLTexture::getSize() const
		{
			return TextureSize;
		}

		//! copies the the texture into an open gl texture.
		void COpenGLTexture::uploadTexture(bool newTexture, void* mipmapData,
				u32 level)
		{
			// check which image needs to be uploaded
			IImage* image = level ? MipImage : Image;

			IRR_ASSERT(image);

			// get correct opengl color data values
			GLenum oldInternalFormat = InternalFormat;
			GLint filtering;
			InternalFormat = getOpenGLFormatAndParametersFromColorFormat(
					ColorFormat, filtering, PixelFormat, PixelType);
			// make sure we don't change the internal format of existing images
			if (!newTexture)
				InternalFormat = oldInternalFormat;

			Driver->setActiveTexture(0, this);

			IRR_ASSERT(!Driver->haveError());

			// mipmap handling for main texture
			if (!level && newTexture)
			{
#ifndef DISABLE_MIPMAPPING
#ifdef GL_SGIS_generate_mipmap
				// auto generate if possible and no mipmap data is given
				if (HasMipMaps && !mipmapData
				//FIXME
				//&& Driver->queryFeature(EVDF_MIP_MAP_AUTO_UPDATE)
						)
				{

//					if (Driver->getTextureCreationFlag(
//							ETCF_OPTIMIZED_FOR_SPEED))
//						glHint(GL_GENERATE_MIPMAP_HINT_SGIS, GL_FASTEST);
//					else if (Driver->getTextureCreationFlag(
//							ETCF_OPTIMIZED_FOR_QUALITY))
//						glHint(GL_GENERATE_MIPMAP_HINT_SGIS, GL_NICEST);
//					else
					glHint(GL_GENERATE_MIPMAP_HINT_SGIS, GL_DONT_CARE);
					// automatically generate and update mipmaps
					glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

					//FIXME
//					AutomaticMipmapUpdate=true;
				}
				else
#endif

				{
					// Either generate manually due to missing capability
					// or use predefined mipmap data
//					AutomaticMipmapUpdate = false;
//					regenerateMipMapLevels(mipmapData);
				}
				//FIXME: refactor it
				if (false)
//				if (HasMipMaps) // might have changed in regenerateMipMapLevels
				{
					// enable bilinear mipmap filter
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
							GL_LINEAR_MIPMAP_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
							GL_LINEAR);
				}
				else
#else
				//Did not create OpenGL texture mip maps.
				HasMipMaps=false;
#endif
				{
					// enable bilinear filter without mipmaps
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
							GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
							GL_LINEAR);
				}
			}

			// now get image data and upload to GPU
			void* source = image->lock();
			if (newTexture)
			{
				glTexImage2D(GL_TEXTURE_2D, level, InternalFormat,
						image->getDimension().Width,
						image->getDimension().Height, 0, PixelFormat, PixelType,
						source);
			}
			else
			{
				glTexSubImage2D(GL_TEXTURE_2D, level, 0, 0,
						image->getDimension().Width,
						image->getDimension().Height, PixelFormat, PixelType,
						source);
			}
			image->unlock();

			IRR_ASSERT(!Driver->haveError());
		}

		//! return open gl texture name
		GLuint COpenGLTexture::getOpenGLTextureName() const
		{
			return TextureName;
		}

		//! returns color format of texture
		EColorFormat COpenGLTexture::getColorFormat() const
		{
			return ColorFormat;
		}

		//! Get opengl values for the GPU texture storage
		GLint COpenGLTexture::getOpenGLFormatAndParametersFromColorFormat(
				EColorFormat format, GLint& filtering, GLenum& colorformat,
				GLenum& type)
		{
			// default
			filtering = GL_LINEAR;
			colorformat = GL_RGBA;
			type = GL_UNSIGNED_BYTE;

			switch (format)
			{
				case ECF_A1R5G5B5:
				{
					colorformat = GL_BGRA_EXT;
					type = GL_UNSIGNED_SHORT_1_5_5_5_REV;

					return GL_RGBA;
				}
				case ECF_R5G6B5:
				{
					colorformat = GL_BGR;
					type = GL_UNSIGNED_SHORT_5_6_5_REV;

					return GL_RGB;
				}
				case ECF_R8G8B8:
				{
					colorformat = GL_BGR;
					type = GL_UNSIGNED_BYTE;

					return GL_RGB;
				}
				case ECF_A8R8G8B8:
				{
					colorformat = GL_BGRA_EXT;
					type = GL_UNSIGNED_INT_8_8_8_8_REV;

					return GL_RGBA;
					// Floating Point texture formats. Thanks to Patryk "Nadro" Nadrowski.
				}
				case ECF_R16F:
				{
					filtering = GL_NEAREST;
					colorformat = GL_RED;
					type = GL_FLOAT;

					return GL_R16F;
				}
				case ECF_G16R16F:
				{
					filtering = GL_NEAREST;
					colorformat = GL_RG;
					type = GL_FLOAT;

					return GL_RG16F;
				}
				case ECF_A16B16G16R16F:
				{
					filtering = GL_NEAREST;
					colorformat = GL_RGBA;
					type = GL_FLOAT;

					return GL_RGBA16F_ARB;
				}
				case ECF_R32F:
				{
					filtering = GL_NEAREST;
					colorformat = GL_RED;
					type = GL_FLOAT;

					return GL_R32F;
				}
				case ECF_G32R32F:
				{
					filtering = GL_NEAREST;
					colorformat = GL_RG;
					type = GL_FLOAT;

					return GL_RG32F;
				}
				case ECF_A32B32G32R32F:
				{
					filtering = GL_NEAREST;
					colorformat = GL_RGBA;
					type = GL_FLOAT;

					return GL_RGBA32F_ARB;
				}
				default:
				{
					// unsupported format
					IRR_ASSERT(false);

					return GL_RGBA8;
				}
			}
		}

		EDriverType COpenGLTexture::getType() const
		{
			return EDT_OPENGL;
		}

	} /* namespace video */
} /* namespace irrgame */
