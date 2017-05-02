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
//	/**
//	*** @class  Signal
//	***
//	*** @brief
//	**/
//	class Signal
//	{
//	private:
//	    const std::string TAG = "Signal";
//
//	protected:
//
//	public:
//	    Signal();
//	    template <typename T>
//	    int connect(T & t, std::function<void()>);
//	    void disconnect(int id);
//	    void emit();
//	    ~Signal();
//	};


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
		static std::map<Uint32, std::vector<std::function<void()>>> event_callback;

	public:
		IEventListener();
		SDL_Event * getEvent();
		virtual void registerEvent(Uint32 code, std::function<void()> callback);
		static void callEvent(Uint32 code);
		~IEventListener();
	};

    /**
    *** @class WindowListener
    ***
    *** @var
    **/
    class WindowListener : public IEventListener
    {
    private:
        const std::string TAG = "WindowListener";

    protected:
        //static std::map<Uint32, std::vector<std::function<void()>>> event_callback;

    public:
        WindowListener();
        /*void registerEvent(Uint32 code, std::function<void()> callback);
        static void callEvent(Uint32 code);*/
        //virtual void onFocus();
        ~WindowListener();
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
        //static std::map<Uint32, std::vector<std::function<void()>>> event_callback;

	public:
	    KeyboardListener();
	    /*void registerEvent(Uint32 code, std::function<void()> callback);
		static void callEvent(Uint32 code);*/
		//virtual void onKeyDown();
		//virtual void onKeyUp();
	    virtual ~KeyboardListener();
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
        //static std::map<Uint32, std::vector<std::function<void()>>> event_callback;

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
        //static std::map<Uint32, std::vector<std::function<void()>>> event_callback;

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
        //static std::map<Uint32, std::vector<std::function<void()>>> event_callback;

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
        //static std::map<Uint32, std::vector<std::function<void()>>> event_callback;

	public:
	    FingerListener();
	    ~FingerListener();
	};

}


#endif // EVENT_LISTENER_H_INCLUDED
