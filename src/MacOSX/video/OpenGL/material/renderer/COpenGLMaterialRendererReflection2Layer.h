/*
 * COpenGLMaterialRendererReflection2Layer.h
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#ifndef COPENGLMATERIALRENDERERREFLECTION2LAYER_H_
#define COPENGLMATERIALRENDERERREFLECTION2LAYER_H_

#include "COpenGLMaterialRenderer.h"

namespace irrgame
{
	namespace video
	{
		//! reflection 2 layer material renderer
		class COpenGLMaterialRendererReflection2Layer: public COpenGLMaterialRenderer
		{
			public:

				//! Default constructor
				COpenGLMaterialRendererReflection2Layer(IVideoDriver* driver);

				//! Destructor
				virtual ~COpenGLMaterialRendererReflection2Layer();

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

				//! Called by the IVideoDriver to unset this material.
				/** Called during the IVideoDriver::setMaterial() call before the new
				 material will get the OnSetMaterial() call. */
				virtual void OnUnsetMaterial();
		};

	} /* namespace video */
} /* namespace irrgame */
#endif /* COPENGLMATERIALRENDERERREFLECTION2LAYER_H_ */
