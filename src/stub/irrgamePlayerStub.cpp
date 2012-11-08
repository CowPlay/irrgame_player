/*
 * irrgamePlayer.cpp
 *
 *  Created on: Jul 26, 2012
 *      Author: gregorytkach
 */

#include "irrgamePlayerStub.h"
#include "events/engine/SharedEventScheduler.h"
#include "video/image/IImage.h"
#include "video/color/EColorFormat.h"
#include "MacOSX/video/OpenGL/COpenGLTexture.h"
#include "io/SharedFileSystem.h"

namespace irrgame
{
	//!Default constructor
	irrgamePlayerStub::irrgamePlayerStub() :
			ConfigReader(0), SceneManager(0), VideoDriver(0), VideoModeList(0), UserEventsHandler(
					0), Timer(0)
	{
		ConfigReader = io::createPlayerConfigReader();

		SceneManager = scene::createSceneManager();

		//FIXME: read config from file or make default config for device before create video driver

		VideoModeList = video::createVideoModeList();

		//create
		UserEventsHandler = events::createUserEventsHandler();

		//create and run actions pool
		events::SharedEventScheduler::getInstance().startProcess();
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

		io::IReadFile* file =
				io::SharedFileSystem::getInstance().createReadFile(
						"/Users/gregorytkach/workspace/irrgame_sdk/src/vendors/libpng/pngtest.png");

		video::IImage* img = video::IImage::createImage(file);

		video::ITexture* t =
				new video::COpenGLTexture(img,
						"/Users/gregorytkach/workspace/irrgame_sdk/src/vendors/libpng/pngbar.png",
						0, VideoDriver);

		while (runInternal())
		{
			utils::ITimer::tick();

			events::SharedEventScheduler::getInstance().proceedNextRealTimeEvent();

			VideoDriver->beginScene();

			VideoDriver->draw2DImage(t, vector2di(50, 50),
					recti(50, 50, 150, 150));
//scenemanager->drawAll();

			VideoDriver->endScene();
		}

		//stop events handler
		UserEventsHandler->stopEventProcess();
	}
} /*end namespace irrgame*/

