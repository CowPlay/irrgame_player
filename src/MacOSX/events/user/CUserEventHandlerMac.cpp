/*
 * CUserEventHandler.cpp
 *
 *  Created on: Oct 23, 2012
 *      Author: gregorytkach
 */

#include "CUserEventHandlerMac.h"

#ifdef COMPILECONFIGMACOSX_H_

#include "events/user/IUserEvent.h"

#include <objc/message.h>
#define SELECTOR(__x__) (sel_registerName(__x__))
#define CLASS(__x__) (objc_getClass(__x__))
#define SEND_OBJC_MESSAGE(__object__, __message__) (objc_msgSend(__object__, SELECTOR(__message__)))
#define SEND_OBJC_MESSAGE_WITH_OBJECT(__instance__, __message__, __object__) (objc_msgSend(__instance__, SELECTOR(__message__), __object__))

namespace irrgame
{
	namespace events
	{

		//! Default constructor
		CUserEventHandlerMac::CUserEventHandlerMac() :
				IUserEventHandler()
		{
			initKeyMap();
			initCursorsInfo();
			initKeyStates();
		}

		//! Destructor
		CUserEventHandlerMac::~CUserEventHandlerMac()
		{
		}

		void CUserEventHandlerMac::initKeyMap()
		{
			KeyMap.insert(0xF700, EUK_UP);		//NSUpArrowFunctionKey
			KeyMap.insert(0xF701, EUK_DOWN);	//NSDownArrowFunctionKey
			KeyMap.insert(0xF702, EUK_LEFT);	//NSLeftArrowFunctionKey
			KeyMap.insert(0xF703, EUK_RIGHT);	//NSRightArrowFunctionKey

			KeyMap.insert(0xF704, EUK_F1);		//NSF1FunctionKey
			KeyMap.insert(0xF705, EUK_F2);		//NSF2FunctionKey
			KeyMap.insert(0xF706, EUK_F3);		//NSF3FunctionKey
			KeyMap.insert(0xF707, EUK_F4);		//NSF4FunctionKey
			KeyMap.insert(0xF708, EUK_F5);		//NSF5FunctionKey
			KeyMap.insert(0xF709, EUK_F6);		//NSF6FunctionKey
			KeyMap.insert(0xF70A, EUK_F7);		//NSF7FunctionKey
			KeyMap.insert(0xF70B, EUK_F8);		//NSF8FunctionKey
			KeyMap.insert(0xF70C, EUK_F9);		//NSF9FunctionKey
			KeyMap.insert(0xF70D, EUK_F10);		//NSF10FunctionKey
			KeyMap.insert(0xF70E, EUK_F11);		//NSF11FunctionKey
			KeyMap.insert(0xF70F, EUK_F12);		//NSF12FunctionKey

			KeyMap.insert(0xF729, EUK_HOME);	//NSHomeFunctionKey
			KeyMap.insert(0xF72B, EUK_END);		//NSEndFunctionKey
			KeyMap.insert(0xF727, EUK_INSERT);	//NSInsertFunctionKey
			KeyMap.insert(0xF728, EUK_DELETE);	//NSDeleteFunctionKey

//			KeyMap.insert(0xF746, EUK_HELP); 	//NSHelpFunctionKey
//			KeyMap.insert(0xF741, EUK_SELECT); 	//NSSelectFunctionKey
//			KeyMap.insert(0xF738, EUK_PRINT);	//NSPrintFunctionKey
//			KeyMap.insert(0xF742, EUK_EXECUT);	//NSExecuteFunctionKey
//			KeyMap.insert(0xF72E, EUK_SNAPSHOT);	//NSPrintScreenFunctionKey
//			KeyMap.insert(0xF730, EUK_PAUSE);	//NSPauseFunctionKey
//			KeyMap.insert(0xF72F, EUK_SCROLL);	//NSScrollLockFunctionKey

			KeyMap.insert(0x7F, EUK_BACKSPACE);
			KeyMap.insert(0x09, EUK_TAB);
			KeyMap.insert(0x0D, EUK_RETURN);
			KeyMap.insert(0x03, EUK_RETURN);
			KeyMap.insert(0x1B, EUK_ESCAPE);

			KeyMap.insert(0x2E, events::EUK_PERIOD);

			//TODO: add all symbols
		}

		//Platform dependent
		void CUserEventHandlerMac::initCursorsInfo()
		{
			CursorsInfo.insert(0, new SCursorInfo(0, ECS_RELEASED));
		}

		//! This func must call from player when any key event from user detected.
		void CUserEventHandlerMac::handleKeyEvent(void* e)
		{
			IUserEvent* userEvent;

			objc_object* event = (objc_object*) e;

			EUserKeys key = EUK_COUNT;
			EUserKeyStates keyState = EUKS_COUNT;

			core::map<s32, EUserKeys>::Iterator it;

			intptr_t eventType = (intptr_t) SEND_OBJC_MESSAGE(event, "type");

			switch (eventType)
			{
				case 10: //NSKeyDown
				case 11: //NSKeyUp
				{
					id str; //NSString *str;
					str =
							SEND_OBJC_MESSAGE(event, "charactersIgnoringModifiers");

					s32 c;

					if ((str)
							&& ((intptr_t) SEND_OBJC_MESSAGE(str, "length")) > 0){

						c =
								(u32) ((intptr_t) SEND_OBJC_MESSAGE_WITH_OBJECT(str, "characterAtIndex:", 0));
					}
					else
						IRR_ASSERT(false);

					printf("%u", c);

					it = KeyMap.find(c);

					//get state

//						cStr =
//								(u8*) SEND_OBJC_MESSAGE_WITH_OBJECT(str, "cStringUsingEncoding:", 12); //12 = NSWindowsCP1252StringEncoding

//						if (cStr && strlen((c8*) cStr) > 0)
//						{
//						}

					break;
				}

				case 12: //NSFlagsChanged
				{

					bool shiftWasPressed =
							(u32) ((intptr_t) SEND_OBJC_MESSAGE(event, "modifierFlags"))
									& (1 << 17); //1<<17 = NSShiftKeyMask

					bool controlWasPressed =
							(u32) ((intptr_t) SEND_OBJC_MESSAGE(event, "modifierFlags"))
									& (1 << 18); //1<<18 = NSControlKeyMask

//					bool altWasPressed =
//							(u32) ((intptr_t) SEND_OBJC_MESSAGE(event, "modifierFlags"))
//									& (1 << 19); //1<<29 = NSControlKeyMask
//
//					bool cmdWasPressed =
//							(u32) ((intptr_t) SEND_OBJC_MESSAGE(event, "modifierFlags"))
//									& (1 << 20); //1<<20 = NSCommandKeyMask
//
//					bool fnWasPressed =
//							(u32) ((intptr_t) SEND_OBJC_MESSAGE(event, "modifierFlags"))
//									& (1 << 23); //1<<23 = NSCommandKeyMask

					if (shiftWasPressed)
					{
						key = EUK_SHIFT;
					}
					else if (controlWasPressed)
					{
						key = EUK_ALT;
					}

					break;
				}
				default:
				{
					IRR_ASSERT(false);
					break;
				}
			}

			//create event
			userEvent = createUserEvent(key, keyState);

			this->onEvent(userEvent);

//			SEND_OBJC_MESSAGE(str, "release");
		}

		//! This func must call from player when any mouse event from user detected.
		//Platform dependent
		void CUserEventHandlerMac::handleMouseEvent(void* e)
		{
			IUserEvent* userEvent;
			SCursorInfo* cursorInfo = CursorsInfo[0];

			objc_object* event = (objc_object*) e;

			core::map<s32, EUserKeys>::Iterator it;

			intptr_t eventType = (intptr_t) SEND_OBJC_MESSAGE(event, "type");

			switch (eventType)
			{
				case 1: //NSLeftMouseDown
				{
					if (cursorInfo->State == ECS_PRESSED
							|| cursorInfo->State == ECS_CURSOR_DRAGGED
							|| cursorInfo->State == ECS_DOWN)
					{
						cursorInfo->State = ECS_DOWN;
					}
					else
					{
						cursorInfo->State = ECS_PRESSED;
					}

					break;
				}
				case 2: //NSLeftMouseUp
				{
					cursorInfo->State = ECS_RELEASED;
					break;
				}
				case 3: //NSRightMouseDown
				{
					break;
				}
				case 4: //NSRightMouseUp
				{
					break;
				}
				case 5: //NSMouseMoved
				{
					cursorInfo->State = ECS_CURSOR_MOVED;
					//TODO: get pos
					break;
				}
				case 6: //NSLeftMouseDragged
				{
					cursorInfo->State = ECS_CURSOR_DRAGGED;
					//TODO: get pos
					break;
				}
				case 7: //NSRightMouseDragged
				{
					break;
				}
				case 22: //NSScrollWheel
				{
					break;
				}
//				case 25: //NSOtherMouseDown
//				case 26: //NSOtherMouseUp
				case 27: //NSOtherMouseDragged
				{
					break;
				}
				default:
				{
					//not implemented
					IRR_ASSERT(false);
					break;
				}
			}

			userEvent = createUserEvent(cursorInfo);

			this->onEvent(userEvent);
		}

		//! Internal function. Please do not use.
		IUserEventHandler * createUserEventsHandler()
		{
			return new CUserEventHandlerMac;
		}

	} /* namespace events */
} /* namespace irrgame */

#undef SEND_OBJC_MESSAGE_WITH_OBJECT
#undef SEND_OBJC_MESSAGE
#undef CLASS
#undef SELECTOR

#endif /* COMPILECONFIGMACOSX_H_ */
