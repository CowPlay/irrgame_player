/*
 * irrgamePlayer.cpp
 *
 *  Created on: Jul 26, 2012
 *      Author: gregorytkach
 */
#include "irrgamePlayerStub.h"
namespace irrgame
{
	//!Default constructor
	irrgamePlayerStub::irrgamePlayerStub() :
			FileSystem(0)
	{

	}

	//! Destructor
	irrgamePlayerStub::~irrgamePlayerStub()
	{

	}

	//! Gets pointer to filesystem
	//! @return - pointer to filesystem
	io::IFileSystem* irrgamePlayerStub::getFileSystem()
	{
		return FileSystem;
	}

}

