/*
 * irrgamePlayer.cpp
 *
 *  Created on: Jul 26, 2012
 *      Author: gregorytkach
 */
#include "irrgamePlayerStub.h"
#include "io/IFileSystem.h"
#include "io/CConfigReader.h"
namespace irrgame
{
	//!Default constructor
	irrgamePlayerStub::irrgamePlayerStub() :
			FileSystem(0)
	{
//		FileSystem = io::createFileSystem();
		//create and run thread pool
	}

	//! Destructor
	irrgamePlayerStub::~irrgamePlayerStub()
	{
		if (FileSystem)
			FileSystem->drop();
	}

	void irrgamePlayerStub::readConfig(const io::path& file)
	{
		io::CConfigReader::readConfig(file);
	}

	//! Gets pointer to filesystem
	//! @return - pointer to filesystem
	io::IFileSystem* irrgamePlayerStub::getFileSystem()
	{
		return FileSystem;
	}

}

