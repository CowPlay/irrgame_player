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

			//! Gets pointer to config reader
			//! @return - pointer to config reader
			virtual io::IPlayerConfigReader* getConfigReader();

		protected:
			//!Default constructor
			irrgamePlayerStub();

		protected:
			io::IPlayerConfigReader* ConfigReader;
	};
}

#endif /* IRRGAMEPLAYERSTUB_H_ */
