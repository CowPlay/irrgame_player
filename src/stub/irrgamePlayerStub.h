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

			virtual void readConfig(const core::stringc& file);

			//! Gets pointer to filesystem
			//! @return - pointer to filesystem
			virtual io::IFileSystem* getFileSystem();

		protected:
			//!Default constructor
			irrgamePlayerStub();

		protected:
			io::IFileSystem* FileSystem;
	};
}

#endif /* IRRGAMEPLAYERSTUB_H_ */
