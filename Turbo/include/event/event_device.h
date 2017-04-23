#ifndef EVENT_DEVICE_H_INCLUDED
#define EVENT_DEVICE_H_INCLUDED

#include "event/event_listener.h"

namespace EVENT
{
    /**
    *** @class  IDevice
    ***
    *** @brief
    **/
    class IDevice
    {
    private:
        const string TAG = "IDevice";

    protected:

    public:
        IDevice();
        ~IDevice();
    };

    /**
    *** @class  Keyboard
    ***
    *** @brief
    **/
    class Keyboard : public IDevice
    {
    private:
        const string TAG = "Keyboard";

        SDL_Keyboard * keyboard;

    protected:

    public:
        Keyboard();
        ~Keyboard();
    };

    /**
    *** @class  Mouse
    ***
    *** @brief
    **/
    class Mouse : public IDevice
    {
    private:
        const string TAG = "Mouse";

        SDL_Mouse * mouse;

    protected:

    public:
        Mouse();
        ~Mouse();
    };

    /**
    *** @class  Controller
    ***
    *** @brief
    **/
    class Controller : public IDevice
    {
    private:
        const string TAG = "Controller";

        SDL_Controller * controller;

    protected:

    public:
        Controller();
        ~Controller();
    };

    /**
    *** @class  Joystick
    ***
    *** @brief
    **/
    class Joystick : public IDevice
    {
    private:
        const string TAG = "Joystick";

        SDL_Joystick * joystick;

    protected:

    public:
        Joystick();
        ~Joystick();
    };
}

#endif // EVENT_DEVICE_H_INCLUDED
