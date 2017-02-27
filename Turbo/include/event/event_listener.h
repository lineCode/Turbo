#ifndef EVENT_LISTENER_H_INCLUDED
#define EVENT_LISTENER_H_INCLUDED

/**
*** @package 	event_listener
*** @author		Christoph Zorn
*** @date		24.02.2017
***
*** @brief		The event_listener package contains
***
***
**/

#include "event/event.h"

namespace EVENT
{
	/**
	*** @class EventListener
	***
	***
	**/
	class IEventListener
	{
	private:
		const string TAG = "IEventListener";

	protected:

	public:
		IEventListener();
		~IEventListener();
	};

}


#endif // EVENT_LISTENER_H_INCLUDED
