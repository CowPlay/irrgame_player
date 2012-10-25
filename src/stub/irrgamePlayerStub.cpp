/*
 * irrgamePlayer.cpp
 *
 *  Created on: Jul 26, 2012
 *      Author: gregorytkach
 */

#include "irrgamePlayerStub.h"
#include "events/engine/IEventScheduler.h"
#include "video/IVideoDriver.h"

namespace irrgame
{
	//!Default constructor
	irrgamePlayerStub::irrgamePlayerStub() :
			ConfigReader(0), SceneManager(0), VideoDriver(0), VideoModeList(0), UserEventsHandler(0),
			Timer(0)
	{
		ConfigReader = io::createPlayerConfigReader();

		SceneManager = scene::createSceneManager();

		//FIXME: read config from file or make default config for device before create video driver

		VideoModeList = video::createVideoModeList();

		//create
		UserEventsHandler = events::createUserEventsHandler();

		//create and run actions pool
		events::IEventScheduler::getInstance().startProcess();
	}

	//! Destructor
	irrgamePlayerStub::~irrgamePlayerStub()
	{
		if (ConfigReader)
			ConfigReader->drop();

		if (SceneManager)
			SceneManager->drop();

		if (VideoDriver)
			VideoDriver->drop();

		if (UserEventsHandler)
			UserEventsHandler->drop();
	}

	//! Gets pointer to config reader
	io::IPlayerConfigReader* irrgamePlayerStub::getConfigReader()
	{
		return ConfigReader;
	}

	scene::ISceneManager* irrgamePlayerStub::getSceneManager()
	{
		return SceneManager;
	}

	video::IVideoDriver* irrgamePlayerStub::getVideoDriver()
	{
		return VideoDriver;
	}

	//! Returns user event receiver
	events::IUserEventHandler* irrgamePlayerStub::getUserEventsHandler()
	{
		return UserEventsHandler;
	}

	void irrgamePlayerStub::run(irrgameApp* application)
	{
		//TODO: run app in other thread

		//start events handler
		UserEventsHandler->startEventProcess();

		while (runInternal())
		{

			utils::ITimer::tick();

			events::IEventScheduler::getInstance().proceedNextRealTimeEvent();

			VideoDriver->beginScene();
//scenemanager->drawAll();
			VideoDriver->endScene();
		}

		//stop events handler
		UserEventsHandler->stopEventProcess();
	}
}

