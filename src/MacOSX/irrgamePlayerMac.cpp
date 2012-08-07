/*
 * irrgamePlayerMac.h
 *
 *  Created on: Jul 26, 2012
 *      Author: gregorytkach
 */
#include "irrgamePlayerMac.h"
#include "./MacOSX/io/CFileSystemMac.h"
namespace irrgame
{

	//! Default constructor
	irrgamePlayerMac::irrgamePlayerMac()
	{
	}

	//! Destructor
	irrgamePlayerMac::~irrgamePlayerMac()
	{

	}

	//! irrgamePlayer creator
	irrgamePlayer* createIrrgamePlayer()
	{
		return new irrgamePlayerMac;
	}

}
