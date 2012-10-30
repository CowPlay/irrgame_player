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

// Define helpers for cocoa objc calls
#define SELECTOR(__x__) (sel_registerName(__x__))
#define CLASS(__x__) (objc_getClass(__x__))
#define SEND_OBJC_MESSAGE(__object__, __message__) (objc_msgSend(__object__, SELECTOR(__message__)))
#define SEND_OBJC_MESSAGE_WITH_OBJECT(__instance__, __message__, __object__) (objc_msgSend(__instance__, SELECTOR(__message__), __object__))

//Need for handle events
extern CFStringRef NSDefaultRunLoopMode;
struct CGRect;
extern CGRect CGRectMake(s32 x, s32 y, s32 w, s32 h);

namespace irrgame
{
	//! Default consructor
	irrgamePlayerMac::irrgamePlayerMac() :
			CGLContext(0), IsActive(true)
	{

#ifdef DEBUG
		setDebugName("CIrrDeviceMacOSX");
#endif

		applicationLaunching();

		//TODO: create COSOperatior to get hardware information
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

	//! Internal macosx application launching
	void irrgamePlayerMac::applicationLaunching()
	{
		// Creating objc autorelease pool to prevent leaking
		SEND_OBJC_MESSAGE(
				SEND_OBJC_MESSAGE(CLASS("NSAutoreleasePool"), "alloc"), "init");

		// Getting (and initialization) of current application
		SEND_OBJC_MESSAGE(CLASS("NSApplication"), "sharedApplication");

		// Initing the control delegate to bind internal app
		//TODO: make real delegate (port the AppDelegate.mm) for event handeling
		id delegate =
				SEND_OBJC_MESSAGE_WITH_OBJECT((SEND_OBJC_MESSAGE(CLASS("AppDelegate"), "alloc")), "initWithDevice:", this);

		// Binding of delegate to app
		SEND_OBJC_MESSAGE(
				SEND_OBJC_MESSAGE_WITH_OBJECT((CLASS("NSApp")), "setDelegate:", delegate),
				"autorelease");

		// We dont need the bundle because we compiling app without XCode internals
//		 objc_msgSend((CLASS("NSBundle")), SELECTOR("loadNibNamed:owner:"), (CFSTR("MainMenu") ), (SEND_OBJC_MESSAGE(CLASS("NSApp"), "delegate")));

		// Signal to application to mark application ready to work
		SEND_OBJC_MESSAGE(CLASS("NSApp"), "finishLaunching");

		// Set current work directory (for linux/win32 resources style)
		id path =
				SEND_OBJC_MESSAGE(SEND_OBJC_MESSAGE(SEND_OBJC_MESSAGE(CLASS("NSBundle"), "mainBundle"), "bundlePath"), "stringByDeletingLastPathComponent");
		chdir(
				(const char*) SEND_OBJC_MESSAGE(path, "fileSystemRepresentation"));

		// delete path
		SEND_OBJC_MESSAGE(path, "release");
	}

	void irrgamePlayerMac::flush()
	{
		if (CGLContext != NULL)
		{
			// Start batched instructions (low-end)
			glFinish();

			//TODO: check the glFlush or CGLFlush to prevent functional duplicates
			// Request to done queue of batched instructions (high-end)
			CGLFlushDrawable(CGLContext);
		}
	}

	//! Will create macosx cocoa window (not x11)
	void irrgamePlayerMac::createWindow()
	{
		// Alpha channel can have lot a more than 8bit, but typical PC can't support alpha more than 8bit
		s32 alphaSize = 8;

		// Depth size can be increased to 24/32 bits (if we want a very great complex persition) but 16bit it's okay
		// can be 0 for 2D games (paint composition method)
		s32 depthSize = 16;

		// RGB = 24bit (8bit per color) + 8bit for alpha
		s32 bits = 24 + alphaSize;

		//TODO: refactor it to check available resolutions on current device
		//		VideoModeList.setDesktop(CreationParams.Bits, core::dimension2d<u32>(ScreenWidth, ScreenHeight));

		// ported cocoa enum to configure window style
		enum
		{
			NSBorderlessWindowMask = 0,
			NSTitledWindowMask = 1 << 0,
			NSClosableWindowMask = 1 << 1,
			NSMiniaturizableWindowMask = 1 << 2,
			NSResizableWindowMask = 1 << 3
		};

		// Making the default window
		CGRect rect = CGRectMake(0, 0, 800, 600);

		// Create cocoa window and configure it for special style
		Window = objc_msgSend(SEND_OBJC_MESSAGE(CLASS("NSWindow"), "alloc"),
				SELECTOR("initWithContentRect:styleMask:backing:defer:"), rect,
				NSTitledWindowMask + NSClosableWindowMask
						+ NSResizableWindowMask, 2, false);

		IRR_ASSERT(Window);

		// Required attributes for window creating
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

		// Creating macos platform depended opengl context (container for CGLContext what can be placed on cocoa view)
		OGLContext = objc_msgSend(
				SEND_OBJC_MESSAGE(CLASS("NSOpenGLContext"), "alloc"),
				SELECTOR("initWithFormat:shareContext:"), format, NULL);

		SEND_OBJC_MESSAGE(format, "release");

		IRR_ASSERT(OGLContext);

		// Centrate window on display
		SEND_OBJC_MESSAGE(Window, "center");

		// Apply application delegate (AppDelegate) for window here
		SEND_OBJC_MESSAGE_WITH_OBJECT(Window, "setDelegate:",
				SEND_OBJC_MESSAGE(CLASS("NSApp"), "delegate"));

		// Getting root view, what can handle OGLContext view
		id contentView = SEND_OBJC_MESSAGE(Window, "contentView");

		IRR_ASSERT(contentView);

		// Bind the view and OGLContext
		SEND_OBJC_MESSAGE_WITH_OBJECT(OGLContext, "setView:", contentView);

		// Accept handeling mouse events
		SEND_OBJC_MESSAGE_WITH_OBJECT(Window, "setAcceptsMouseMovedEvents:",
				true);

		// Show window
		SEND_OBJC_MESSAGE_WITH_OBJECT(Window, "setIsVisible:", true);

		// Make it upper than other windows
		//TODO: fixit! Not working now
		SEND_OBJC_MESSAGE_WITH_OBJECT(Window, "makeKeyAndOrderFront:", NULL);

		// Getting internal OpenGLContext
		CGLContext =
				(CGLContextObj) SEND_OBJC_MESSAGE(OGLContext, "CGLContextObj");

		// Setting the internal OpenGLContext as default
		CGLSetCurrentContext(CGLContext);

		//GLint newSwapInterval = 1; // enable vsync
		//CGLSetParameter(CGLContext, kCGLCPSwapInterval, &newSwapInterval);
	}

	//! Run player internal. Must be overriden in every realization of player.
	//! Handle user events in this func
	bool irrgamePlayerMac::runInternal()
	{
		// Event handeling

		// Check if application closed
		bool result =
				!((bool) SEND_OBJC_MESSAGE(SEND_OBJC_MESSAGE(CLASS("NSApp"), "delegate"), "isQuit"))
						&& IsActive;

		id event; //NSEvent *event;

		//		storeMouseLocation();
		//

		// Getting next event
		event = objc_msgSend(CLASS("NSApp"),
				SELECTOR("nextEventMatchingMask:untilDate:inMode:dequeue:"),
				(0xffffffffU),
				SEND_OBJC_MESSAGE(CLASS("NSDate"), "distantPast"),
				NSDefaultRunLoopMode, true);

		if (!event)
		{
			// TODO
			//handle cursor stopped event

		}
		else
		{
			// Get type of event
			// here is return type int actually, but id - default cocoa return signature, so we need to convert it to int for handeling
			// ant the short way - get it as "int pointer" - can be withou errors/warnings and can be handled in switch
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
		}
		return result;
	}

	//! irrgamePlayer creator
	irrgamePlayer* createIrrgamePlayer()
	{
		return new irrgamePlayerMac;
	}

} /* namespace irrgame */

// Undefine internal definitions
#undef SEND_OBJC_MESSAGE_WITH_OBJECT
#undef SEND_OBJC_MESSAGE
#undef CLASS
#undef SELECTOR
