/*
 * COpenGLMaterialRenderer.h
 *
 *  Created on: Oct 29, 2012
 *      Author: gregorytkach
 */

#ifndef COPENGLMATERIALRENDERER_H_
#define COPENGLMATERIALRENDERER_H_

#include "video/material/IMaterialRenderer.h"
#include "video/IVideoDriver.h"

namespace irrgame
{
	namespace video
	{
		//! Base class for all internal OpenGL material renderers
		class COpenGLMaterialRenderer: public IMaterialRenderer
		{
			public:

				//! Default constructor
				COpenGLMaterialRenderer(IVideoDriver* driver);

				//! Destructor
				virtual ~COpenGLMaterialRenderer();

			protected:

				IVideoDriver* Driver;
		};
	}  // namespace video
}  // namespace irrgame

#endif /* COPENGLMATERIALRENDERER_H_ */
