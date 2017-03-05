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
		const std::string TAG = "IEventListener";

	protected:
		std::map<Uint32, std::vector<std::function<void()>>> callback;

	public:
		IEventListener();
		virtual void registerCallback(Uint32 code, std::function<void> callback) = 0;
		virtual void callCallback(Uint32 code) = 0;
		~IEventListener();
	};

	/**
	*** @class KeyboardListener
	***
	*** @var
	**/
	class KeyboardListener : public IEventListener
	{
	private:
	    const std::string TAG = "KeyboardListener";

	protected:

	public:
	    KeyboardListener();
	    void registerCallback(Uint32 code, std::function<void()> callback);
		void callCallback(Uint32 code);
	    ~KeyboardListener();
	};

}


#endif // EVENT_LISTENER_H_INCLUDED
