/*
 * IOpenGLExtensionHandler.cpp
 *
 *  Created on: Oct 26, 2012
 *      Author: gregorytkach
 */

#include "IOpenGLExtensionHandler.h"

namespace irrgame
{

	namespace video
	{
		//! Default constructor
		IOpenGLExtensionHandler::IOpenGLExtensionHandler() :
				StencilBuffer(false), MultiTextureExtension(false), TextureCompressionExtension(
						false), MaxTextureUnits(1), MaxLights(1), MaxAnisotropy(
						1), MaxUserClipPlanes(0), MaxAuxBuffers(0), MaxMultipleRenderTargets(
						1), MaxIndices(65535), MaxTextureSize(1), MaxGeometryVerticesOut(
						0), MaxTextureLODBias(0.f), Version(0), ShaderLanguageVersion(
						0)
		{
		}

		//! Destructor
		IOpenGLExtensionHandler::~IOpenGLExtensionHandler()
		{
		}

	}  // namespace video

}  // namespace irrgame
