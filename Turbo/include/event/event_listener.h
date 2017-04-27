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

		SDL_Event * event;

	protected:
		std::map<Uint32, std::vector<std::function<void()>>> callback;

	public:
		IEventListener();
		SDL_Event * getEvent();
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
		void onKeyDown();
		void onKeyUp();
	    ~KeyboardListener();
	};

	/**
	*** @class  MouseListener
	***
	*** @brief
	**/
	class MouseListener : public IEventListener
	{
	private:
	    const string TAG = "MouseListener";

	protected:

	public:
	    MouseListener();
	    void registerCallback(Uint32 code, std::function<void()> callback);
		void callCallback(Uint32 code);
		void onMouseMotion();
		void onMouseButtonDown();
		void onMouseButtonUp();
		void onMouseWheel();
	    ~MouseListener();
	};

	/**
	*** @class  ControllerListener
	***
	*** @brief
	**/
	class ControllerListener : public IEventListener
	{
	private:
		const string TAG = "ControllerListener";

	protected:

	public:
		ControllerListener();
		void onControllerAxisMotion();
		void onControllerButtonDown();
		void onControllerButtonUp();
		~ControllerListener();
	};

	/**
	*** @class  JoystickListener
	***
	*** @brief
	**/
	class JoystickListener : public IEventListener
	{
	private:
	    const string TAG = "JoystickListener";

	protected:

	public:
	    JoystickListener();
	    void onJoyAxisMotion();
	    void onJoyBallMotion();
	    void onJoyHatMotion();
	    void onJoyButtonDown();
	    void onJoyButtonUp();
	    ~JoystickListener();
	};

	/**
	*** @class  FingerListener
	***
	*** @brief
	**/
	class FingerListener : public IEventListener
	{
	private:
	    const string TAG = "FingerListener";

	protected:

	public:
	    FingerListener();
	    ~FingerListener();
	};

}


#endif // EVENT_LISTENER_H_INCLUDED
