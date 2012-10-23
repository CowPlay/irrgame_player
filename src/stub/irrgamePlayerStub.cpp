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
			ConfigReader(0), SceneManager(0), VideoDriver(0), VideoModeList(0), UserEventsHandler(
					0)
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
			events::IEventScheduler::getInstance().proceedNextRealTimeEvent();

			VideoDriver->beginScene();
//scenemanager->drawAll();
			VideoDriver->endScene();
		}

		//stop events handler
		UserEventsHandler->stopEventProcess();
	}



////! send the event to the right receiver
//	void CIrrDeviceStub::postEventFromUser(const SEvent& event)
//		{
//		bool absorbed = false;
//
//		if (UserReceiver)
//			absorbed = UserReceiver->OnEvent(event);
//
//		if (!absorbed && GUIEnvironment)
//			absorbed = GUIEnvironment->postEventFromUser(event);
//
//		scene::ISceneManager* inputReceiver = InputReceivingSceneManager;
//
//		if (!inputReceiver)
//			inputReceiver = SceneManager;
//
//		if (!absorbed && inputReceiver)
//			absorbed = inputReceiver->postEventFromUser(event);
//
//		_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
//		return absorbed;
//		}

}

