/*
 * COpenGLTexture.h
 *
 *  Created on: Oct 16, 2012
 *      Author: gregorytkach
 */

#ifndef COPENGLTEXTURE_H_
#define COPENGLTEXTURE_H_

#include "video/ITexture.h"
#include "video/image/IImage.h"
#include "core/collections/stringc.h"
#include "video/color/EColorFormat.h"
#include "COpenGLDriver.h"

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>

namespace irrgame
{
	namespace video
	{
		class COpenGLTexture: public ITexture
		{
			public:
				//! Default constructor
//				COpenGLTexture(const core::stringc& path);

			//TODO: why driver = 0 by default?
				//! Default constructor
				COpenGLTexture(IImage* surface, const core::stringc& name,
						void* mipmapData = 0, IVideoDriver* driver = 0);

				//! Destructor
				virtual ~COpenGLTexture();

				//! Is it a render target?
				virtual bool isRenderTarget() const;

				//! get important numbers of the image and hw texture
				void getImageValues(IImage* image);

				//! get the desired color format based on texture creation flags and the input format.
				EColorFormat getBestColorFormat(EColorFormat format);

				//! Get original size of the texture.
				/** The texture is usually scaled, if it was created with an unoptimal
				 size. For example if the size was not a power of two. This method
				 returns the size of the texture it had before it was scaled. Can be
				 useful when drawing 2d images on the screen, which should have the
				 exact size of the original texture. U2se ITexture::getSize() if you want
				 to know the real size it has now stored in the system.
				 \return The original size of the texture. */
				virtual const dimension2du& getOriginalSize() const;

				//! Returns size of the texture.
				virtual const dimension2du& getSize() const;

				//! copies the texture into an OpenGL texture.
				/** \param newTexture True if method is called for a newly created texture for the first time. Otherwise call with false to improve memory handling.
				 \param mipmapData Pointer to raw mipmap data, including all necessary mip levels, in the same format as the main texture image.
				 \param mipLevel If set to non-zero, only that specific miplevel is updated, using the MipImage member. */
				void uploadTexture(bool newTexture = false,
						void* mipmapData = 0, u32 mipLevel = 0);

				//! return open gl texture name
				GLuint getOpenGLTextureName() const;

				//! returns color format of texture
				virtual EColorFormat getColorFormat() const;

				//! Get the OpenGL color format parameters based on the given Irrlicht color format
				GLint getOpenGLFormatAndParametersFromColorFormat(
						EColorFormat format, GLint& filtering,
						GLenum& colorformat, GLenum& type);

				EDriverType getType() const;

			protected:
				IImage* Image;
				IImage* MipImage;


				dimension2du ImageSize;
				dimension2du TextureSize;

				GLuint TextureName;
				GLint InternalFormat;
				GLenum PixelFormat;
				GLenum PixelType;

				bool HasMipMaps;

				EColorFormat ColorFormat;
				COpenGLDriver* Driver;

				bool IsRenderTarget;
		};
	} /* namespace video */
} /* namespace irrgame */
#endif /* COPENGLTEXTURE_H_ */
