/*
 * COpenGLTexture.h
 *
 *  Created on: Oct 16, 2012
 *      Author: gregorytkach
 */

#ifndef COPENGLTEXTURE_H_
#define COPENGLTEXTURE_H_

#include "video/ITexture.h"
#include "core/collections/irrstring.h"

namespace irrgame
{
	namespace video
	{

		class COpenGLTexture: public ITexture
		{
			public:
				//! Default constructor
				COpenGLTexture(const core::stringc& path);

				//! Destructor
				virtual ~COpenGLTexture();
		};

	} /* namespace video */
} /* namespace irrgame */
#endif /* COPENGLTEXTURE_H_ */
