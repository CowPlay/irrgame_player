/*
 * CUserEventHandler.h
 *
 *  Created on: Oct 23, 2012
 *      Author: gregorytkach
 */

#ifndef CUSEREVENTHANDLER_H_
#define CUSEREVENTHANDLER_H_

#include "events/user/IUserEventHandler.h"

namespace irrgame
{
	namespace events
	{

		class CUserEventHandler: public IUserEventHandler
		{
			public:
				//! Default constructor
				CUserEventHandler();

				//! Destructor
				virtual ~CUserEventHandler();

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
