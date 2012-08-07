/*
 * irrgamePlayerMac.h
 *
 *  Created on: Jul 26, 2012
 *      Author: gregorytkach
 */



#ifndef IRRGAMEPLAYERMAC_H_
#define IRRGAMEPLAYERMAC_H_
#include "./stub/irrgamePlayerStub.h"
#include "wchar.h"
namespace irrgame
{
	class irrgamePlayerMac: public irrgamePlayerStub
	{
		public:

			//! Default constructor
			irrgamePlayerMac();

			//! Destructor
			virtual ~irrgamePlayerMac();

	};
}

#endif /* IRRGAMEPLAYERMAC_H_ */
