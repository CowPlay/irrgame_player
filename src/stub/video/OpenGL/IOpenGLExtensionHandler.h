/*
 * IOpenGLExtensionHandler.h
 *
 *  Created on: Oct 26, 2012
 *      Author: gregorytkach
 */

#ifndef IOPENGLEXTENSIONHANDLER_H_
#define IOPENGLEXTENSIONHANDLER_H_

#include "core/irrgamebase.h"
#include "video/EVideoDriverFeatures.h"
#include "EOpenGLFeatures.h"
#include <OpenGL/gl.h>

namespace irrgame
{
	namespace video
	{
		class IOpenGLExtensionHandler
		{
				/*
				 * Static methods
				 */
			public:

				//! Singleton realization
				static IOpenGLExtensionHandler& getInstance();

				/*
				 * Instance methods
				 */

			public:
				//! Default constructor
				IOpenGLExtensionHandler();

				//! Destructor
				virtual ~IOpenGLExtensionHandler();

				// deferred initialization
				virtual void initExtensions(bool stencilBuffer) = 0;

				//! queries the features of the driver, returns true if feature is available
				virtual bool queryFeature(
						EVideoDriverFeatures feature) const = 0;

				//! queries the features of the driver, returns true if feature is available
				virtual bool queryOpenGLFeature(
						EOpenGLFeatures feature) const = 0;

				//! show all features with availablity
				virtual void dump() const = 0;

			public:
				// Some variables for properties
				bool StencilBuffer;
				bool MultiTextureExtension;
				bool TextureCompressionExtension;

				/*
				 * Some non-boolean properties
				 */

				//! Maxmimum texture layers supported by the fixed pipeline
				u8 MaxTextureUnits;
				//! Maximum hardware lights supported
				u8 MaxLights;
				//! Maximal Anisotropy
				u8 MaxAnisotropy;
				//! Number of user clipplanes
				u8 MaxUserClipPlanes;
				//! Number of auxiliary buffers
				u8 MaxAuxBuffers;
				//! Number of rendertargets available as MRTs
				u8 MaxMultipleRenderTargets;
				//! Optimal number of indices per meshbuffer
				u32 MaxIndices;
				//! Maximal texture dimension
				u32 MaxTextureSize;
				//! Maximal vertices handled by geometry shaders
				u32 MaxGeometryVerticesOut;
				//! Maximal LOD Bias
				f32 MaxTextureLODBias;
				//! Minimal and maximal supported thickness for lines without smoothing
				GLfloat DimAliasedLine[2];
				//! Minimal and maximal supported thickness for points without smoothing
				GLfloat DimAliasedPoint[2];
				//! Minimal and maximal supported thickness for lines with smoothing
				GLfloat DimSmoothedLine[2];
				//! Minimal and maximal supported thickness for points with smoothing
				GLfloat DimSmoothedPoint[2];

				//! OpenGL version as Integer: 100*Major+Minor, i.e. 2.1 becomes 201
				u16 Version;
				//! GLSL version as Integer: 100*Major+Minor
				u16 ShaderLanguageVersion;

			protected:

			protected:
				// the global feature array
				bool FeatureAvailable[IRR_OpenGL_Feature_Count];
		};
	}  // namespace video

}  // namespace irrgame

#endif /* IOPENGLEXTENSIONHANDLER_H_ */
