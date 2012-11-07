/*
 * CUserEventHandler.h
 *
 *  Created on: Oct 23, 2012
 *      Author: gregorytkach
 */

#include "playerCompileConfig.h"

#ifdef COMPILECONFIGMACOSX_H_

#ifndef CUSEREVENTHANDLER_H_
#define CUSEREVENTHANDLER_H_

#include "events/user/IUserEventHandler.h"

namespace irrgame
{
	namespace events
	{

		class CUserEventHandlerMac: public IUserEventHandler
		{
			public:
				//! Default constructor
				CUserEventHandlerMac();

				//! Destructor
				virtual ~CUserEventHandlerMac();

				//! This func must call from player when any key event from user detected.
				//Platform dependent
				void handleKeyEvent(void* e);

				//! This func must call from player when any mouse event from user detected.
				//Platform dependent
				void handleMouseEvent(void* e);

			protected:
				//Platform dependent
				virtual void initKeyMap();
				//Platform dependent
				virtual void initCursorsInfo();
		};

	} /* namespace events */
} /* namespace irrgame */

#endif /* CUSEREVENTHANDLER_H_ */

#endif /* COMPILECONFIGMACOSX_H_ */
