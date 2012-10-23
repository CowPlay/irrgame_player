/*
 * irrgamePlayerMac.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: gregorytkach
 */

#include "irrgamePlayerMac.h"
#include <stdio.h>

#include <objc/message.h>
#include <CoreFoundation/CFString.h>
#include <Carbon/Carbon.h>

#include "events/user/EUserKeys.h"
#include "events/user/IUserEvent.h"

#define SELECTOR(__x__) (sel_registerName(__x__))
#define CLASS(__x__) (objc_getClass(__x__))
#define SEND_OBJC_MESSAGE(__object__, __message__) (objc_msgSend(__object__, SELECTOR(__message__)))
#define SEND_OBJC_MESSAGE_WITH_OBJECT(__instance__, __message__, __object__) (objc_msgSend(__instance__, SELECTOR(__message__), __object__))

//Need for handle events
extern CFStringRef NSDefaultRunLoopMode;

namespace irrgame
{

	//! Default consructor
	irrgamePlayerMac::irrgamePlayerMac() :
			CGLContext(0), IsActive(true)
	{
#ifdef DEBUG
		setDebugName("CIrrDeviceMacOSX");
#endif

		SEND_OBJC_MESSAGE(
				SEND_OBJC_MESSAGE(CLASS("NSAutoreleasePool"), "alloc"), "init");
		SEND_OBJC_MESSAGE(CLASS("NSApplication"), "sharedApplication");
		id delegate =
				SEND_OBJC_MESSAGE_WITH_OBJECT((SEND_OBJC_MESSAGE(CLASS("AppDelegate"), "alloc")), "initWithDevice:", this);

		SEND_OBJC_MESSAGE(
				SEND_OBJC_MESSAGE_WITH_OBJECT((CLASS("NSApp")), "setDelegate:", delegate),
				"autorelease");

		objc_msgSend((CLASS("NSBundle")), SELECTOR("loadNibNamed:owner:"),
				(CFSTR("MainMenu") ),
				(SEND_OBJC_MESSAGE(CLASS("NSApp"), "delegate")));

		SEND_OBJC_MESSAGE(CLASS("NSApp"), "finishLaunching");

		id path =
				SEND_OBJC_MESSAGE(SEND_OBJC_MESSAGE(SEND_OBJC_MESSAGE(CLASS("NSBundle"), "mainBundle"), "bundlePath"), "stringByDeletingLastPathComponent");

		chdir(
				(const char*) SEND_OBJC_MESSAGE(path, "fileSystemRepresentation"));
		SEND_OBJC_MESSAGE(path, "release");

		//		Operator = new COSOperator(name.version);

		createWindow();
		//
		//		setResizable(false);
		//
		//		CursorControl = new CCursorControl(CreationParams.WindowSize, this);
		VideoDriver = video::createVideoDriver(this);

		//		createGUIAndScene();
	}

	//! Destructor
	irrgamePlayerMac::~irrgamePlayerMac()
	{
	}

	void irrgamePlayerMac::flush()
	{
		if (CGLContext != NULL)
		{
			glFinish();
			CGLFlushDrawable(CGLContext);
		}
	}

	void irrgamePlayerMac::createWindow()
	{
		s32 alphaSize = 8;
		s32 depthSize = 16;
		s32 bits = 32; // video mode 24 bit + 8 alpha

		//		VideoModeList.setDesktop(CreationParams.Bits, core::dimension2d<u32>(ScreenWidth, ScreenHeight));

		enum
		{
			NSBorderlessWindowMask = 0,
			NSTitledWindowMask = 1 << 0,
			NSClosableWindowMask = 1 << 1,
			NSMiniaturizableWindowMask = 1 << 2,
			NSResizableWindowMask = 1 << 3
		};

		CGRect rect = CGRectMake(0, 0, 800, 600);
//		{ 0, 0, 800, 600 };

		Window = objc_msgSend(SEND_OBJC_MESSAGE(CLASS("NSWindow"), "alloc"),
				SELECTOR("initWithContentRect:styleMask:backing:defer:"), rect,
				NSTitledWindowMask + NSClosableWindowMask
						+ NSResizableWindowMask, 2, false);

		IRR_ASSERT(Window);

		s32 windowattribs[] =
		{ 72,	//NSOpenGLPFANoRecovery. Disable all failure recovery systems
				73, //NSOpenGLPFAAccelerated. Choose a hardware accelerated renderer
				12, 		//NSOpenGLPFADepthSize. Number of depth buffer bits
				depthSize, 	//NSOpenGLPFADepthSize value
				8,			//NSOpenGLPFAColorSize. Number of color buffer bits
				bits, 		//NSOpenGLPFAColorSize value
				11, 	//NSOpenGLPFAAlphaSize. Number of alpha component bits
				alphaSize, 	//NSOpenGLPFAAlphaSize value
				55,	//NSOpenGLPFASampleBuffers. Number of multi sample buffers
				1, 			//NSOpenGLPFASampleBuffers value
				56, //NSOpenGLPFASamples. Number of samples per multi sample buffer
				true, //NSOpenGLPFASamples value. True - Antialias is ON, False - Antialias - OFF
				13,			//NSOpenGLPFAStencilSize
				true,//NSOpenGLPFAStencilSize value. True - Stencil buffer is ON, False - Stencil buffer - OFF
				5, //NSOpenGLPFADoubleBuffer. Choose a double buffered pixel format
				0 			//NSOpenGLPixelFormatAttribute
				};

		//disable antialias

		id format;	//NSOpenGLPixelFormat *format;

		//after one fail making pixel format we try 2 more times create it
		for (int i = 0; i < 3; ++i)
		{
			switch (i)
			{
				case 0:
				{
					break;
				}
				case 1:
				{
					// Second try without stencilbuffer
					if (windowattribs[13])
					{
						windowattribs[13] = false;
					}
					else
					{
						continue;
					}

					break;
				}
				case 2:
				{
					// Third try without Doublebuffer
					windowattribs[14] = 0;

					break;
				}
				default:
				{
					IRR_ASSERT(false);
					break;
				}
			}

			//TODO
			format =
					SEND_OBJC_MESSAGE_WITH_OBJECT(SEND_OBJC_MESSAGE(CLASS("NSOpenGLPixelFormat"), "alloc"), "initWithAttributes:", windowattribs);

			if (format)
				break;

		}

		IRR_ASSERT(format);

		OGLContext = objc_msgSend(
				SEND_OBJC_MESSAGE(CLASS("NSOpenGLContext"), "alloc"),
				SELECTOR("initWithFormat:shareContext:"), format, NULL);

		SEND_OBJC_MESSAGE(format, "release");

		IRR_ASSERT(OGLContext);

		SEND_OBJC_MESSAGE(Window, "center");

		SEND_OBJC_MESSAGE_WITH_OBJECT(Window, "setDelegate:",
				SEND_OBJC_MESSAGE(CLASS("NSApp"), "delegate"));

		SEND_OBJC_MESSAGE_WITH_OBJECT(OGLContext, "setView:",
				SEND_OBJC_MESSAGE(Window, "contentView"));

		SEND_OBJC_MESSAGE_WITH_OBJECT(Window, "setAcceptsMouseMovedEvents:",
				true);

		SEND_OBJC_MESSAGE_WITH_OBJECT(Window, "setIsVisible:", true);

		SEND_OBJC_MESSAGE_WITH_OBJECT(Window, "makeKeyAndOrderFront:", NULL);

		CGLContext =
				(CGLContextObj) SEND_OBJC_MESSAGE(OGLContext, "CGLContextObj");

		CGLSetCurrentContext(CGLContext);

		GLint newSwapInterval = 1; // enable vsync
		CGLSetParameter(CGLContext, kCGLCPSwapInterval, &newSwapInterval);
	}

	//! Run player internal. Must be overriden in every realization of player.
	//! Handle user events in this func
	bool irrgamePlayerMac::runInternal()
	{
		bool result =
				!((bool) SEND_OBJC_MESSAGE(SEND_OBJC_MESSAGE(CLASS("NSApp"), "delegate"), "isQuit"))
						&& IsActive;

		id event; //NSEvent *event;

		//		os::Timer::tick();
		//		storeMouseLocation();
		//
		event = objc_msgSend(CLASS("NSApp"),
				SELECTOR("nextEventMatchingMask:untilDate:inMode:dequeue:"),
				(0xffffffffU),
				SEND_OBJC_MESSAGE(CLASS("NSDate"), "distantPast"),
				NSDefaultRunLoopMode, true);
		//		event = [NSApp nextEventMatchingMask:NSAnyEventMask untilDate:[NSDate distantPast] inMode:NSDefaultRunLoopMode dequeue:YES];

		if (!event)
			return result;

//		bzero(&ievent,sizeof(ievent));
		intptr_t eventType = (intptr_t) SEND_OBJC_MESSAGE(event, "type");

		switch (eventType)
		{
			case 1: //NSLeftMouseDown
			case 2: //NSLeftMouseUp
			case 3: //NSRightMouseDown
			case 4: //NSRightMouseUp
			case 5: //NSMouseMoved
			case 6: //NSLeftMouseDragged
			case 7: //NSRightMouseDragged
			case 22: //NSScrollWheel
//			case 25: //NSOtherMouseDown
//			case 26: //NSOtherMouseUp
			case 27: //NSOtherMouseDragged

			{
				UserEventsHandler->handleMouseEvent(event);
				break;
			}
			case 10: //NSKeyDown
			case 11: //NSKeyUp
			case 12: //NSFlagsChanged
			{
				UserEventsHandler->handleKeyEvent(event);
				break;
			}
			default:
//				[NSApp sendEvent:event];
				break;
		}
		return result;
	}

	//! irrgamePlayer creator
	irrgamePlayer* createIrrgamePlayer()
	{
		return new irrgamePlayerMac;
	}

} /* namespace irrgame */

#undef SEND_OBJC_MESSAGE_WITH_OBJECT
#undef SEND_OBJC_MESSAGE
#undef CLASS
#undef SELECTOR
