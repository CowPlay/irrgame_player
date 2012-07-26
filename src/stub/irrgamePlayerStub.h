/*
 * irrgamePlayerStub.h
 *
 *  Created on: Jul 26, 2012
 *      Author: gregorytkach
 */

#ifndef IRRGAMEPLAYERSTUB_H_
#define IRRGAMEPLAYERSTUB_H_
#include "irrgamePlayer.h"
namespace irrgame
{
	class irrgamePlayerStub: public irrgamePlayer
	{
		public:
			//! Destructor
			virtual ~irrgamePlayerStub();

			//! Gets pointer to filesystem
			//! @return - pointer to filesystem
			virtual void getFileSystem();

		protected:
			//!Default constructor
			irrgamePlayerStub();
	};
}

#endif /* IRRGAMEPLAYERSTUB_H_ */
