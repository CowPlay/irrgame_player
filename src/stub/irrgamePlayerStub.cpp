/*
 * irrgamePlayer.cpp
 *
 *  Created on: Jul 26, 2012
 *      Author: gregorytkach
 */
#include "irrgamePlayerStub.h"
#include "actions/IActionScheduler.h"
namespace irrgame
{
	//!Default constructor
	irrgamePlayerStub::irrgamePlayerStub() :
			ConfigReader(0)
	{
		ConfigReader = io::createPlayerConfigReader();

		//create and run actions pool
		actions::IActionScheduler::getInstance().startProcess();
	}

	//! Destructor
	irrgamePlayerStub::~irrgamePlayerStub()
	{
		if (ConfigReader)
			ConfigReader->drop();
	}

	io::IPlayerConfigReader* irrgamePlayerStub::getConfigReader()
	{
		return ConfigReader;
	}

}

