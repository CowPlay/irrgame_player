/*
 * ERenderTarget.h
 *
 *  Created on: Oct 31, 2012
 *      Author: gregorytkach
 */

#ifndef ERENDERTARGET_H_
#define ERENDERTARGET_H_

namespace irrgame
{
	namespace video
	{

		//! Special render targets, which usually map to dedicated hardware
		/** These render targets (besides 0 and 1) need not be supported by gfx cards */
		enum ERenderTarget
		{
			//! Render target is the main color frame buffer
			ERT_FRAME_BUFFER = 0,
			//! Render target is a render texture
			ERT_RENDER_TEXTURE,
			//! Multi-Render target textures
			ERT_MULTI_RENDER_TEXTURES,
			//! Render target is the main color frame buffer
			ERT_STEREO_LEFT_BUFFER,
			//! Render target is the right color buffer (left is the main buffer)
			ERT_STEREO_RIGHT_BUFFER,
			//! Render to both stereo buffers at once
			ERT_STEREO_BOTH_BUFFERS,
			//! Auxiliary buffer 0
			ERT_AUX_BUFFER0,
			//! Auxiliary buffer 1
			ERT_AUX_BUFFER1,
			//! Auxiliary buffer 2
			ERT_AUX_BUFFER2,
			//! Auxiliary buffer 3
			ERT_AUX_BUFFER3,
			//! Auxiliary buffer 4
			ERT_AUX_BUFFER4,

			//! Not used
			ERT_COUNT
		};

	}  // namespace video

}  // namespace irrgame

#endif /* ERENDERTARGET_H_ */
