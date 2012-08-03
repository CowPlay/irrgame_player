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
		FileSystem = new io::CFileSystemMac;
	}

	//! Destructor
	irrgamePlayerMac::~irrgamePlayerMac()
	{
		if (FileSystem)
			FileSystem->drop();
	}

	//! irrgamePlayer creator
	irrgamePlayer* createIrrgamePlayer()
	{
		return new irrgamePlayerMac;
	}

}
