/*
 * ERenderMode.h
 *
 *  Created on: Oct 25, 2012
 *      Author: gregorytkach
 */

#ifndef ERENDERMODE_H_
#define ERENDERMODE_H_

namespace irrgame
{

	namespace video
	{

		//! enumeration for rendering modes such as 2d and 3d for minizing the switching of renderStates.
		enum ERenderMode

		{
			ERM_NONE = 0, // no render state has been set yet.
			ERM_2D,
			// 2d drawing rendermode
			ERM_3D
		// 3d rendering mode
		};

	}  // namespace video

}  // namespace irrgame

#endif /* ERENDERMODE_H_ */
