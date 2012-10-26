/*
 * SUserClipPlane.h
 *
 *  Created on: Oct 25, 2012
 *      Author: gregorytkach
 */

#ifndef SUSERCLIPPLANE_H_
#define SUSERCLIPPLANE_H_

#include "core/irrgameshapes.h"

namespace irrgame
{

	namespace video
	{

		struct SUserClipPlane

		{

				SUserClipPlane() :
						Enabled(false)
				{
				}

				plane3df Plane;
				bool Enabled;
		};
	}  // namespace video

}  // namespace irrgame

#endif /* SUSERCLIPPLANE_H_ */
