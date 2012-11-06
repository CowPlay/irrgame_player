/*
 * COpenGLMaterialRendererSolid.h
 *
 *  Created on: Oct 29, 2012
 *      Author: gregorytkach
 */

#ifndef COPENGLMATERIALRENDERERSOLID_H_
#define COPENGLMATERIALRENDERERSOLID_H_

#include "COpenGLMaterialRenderer.h"

namespace irrgame
{
	namespace video
	{

		//! Solid material renderer
		class COpenGLMaterialRendererSolid: public COpenGLMaterialRenderer
		{
			public:

				//! Default constructor
				COpenGLMaterialRendererSolid(IVideoDriver* driver);

				//! Destructor
				virtual ~COpenGLMaterialRendererSolid();

				//! Called by the IVideoDriver implementation the let the renderer set its needed render states.
				/** This is called during the IVideoDriver::setMaterial() call.
				 When overriding this, you can set some renderstates or for example a
				 vertex or pixel shader if you like.
				 \param material: The new material parameters to be set. The renderer
				 may change the material flags in this material. For example if this
				 material does not accept the zbuffer = true, it can set it to false.
				 This is useful, because in the next lastMaterial will be just the
				 material in this call.
				 \param lastMaterial: The material parameters which have been set before
				 this material.
				 \param resetAllRenderstates: True if all renderstates should really be
				 reset. This is usually true if the last rendering mode was not a usual
				 3d rendering mode, but for example a 2d rendering mode.
				 You should reset really all renderstates if this is true, no matter if
				 the lastMaterial had some similar settings. This is used because in
				 most cases, some common renderstates are not changed if they are
				 already there, for example bilinear filtering, wireframe,
				 gouraudshading, lighting, zbuffer, zwriteenable, backfaceculling and
				 fogenable.
				 \param services: Interface providing some methods for changing
				 advanced, internal states of a IVideoDriver. */
				virtual void OnSetMaterial(const SMaterial& material,
						const SMaterial& lastMaterial,
						bool resetAllRenderstates,
						IMaterialRendererServices* services);

		};

	} /* namespace video */
} /* namespace irrgame */
#endif /* COPENGLMATERIALRENDERERSOLID_H_ */
