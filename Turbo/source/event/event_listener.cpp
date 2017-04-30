#include "event/event_listener.h"

using namespace EVENT;

map<Uint32, vector<function<void()>>> IEventListener::event_callback;
//map<Uint32, vector<function<void()>>> WindowListener::event_callback;
//map<Uint32, vector<function<void()>>> KeyboardListener::event_callback;
//map<Uint32, vector<function<void()>>> MouseListener::event_callback;
//map<Uint32, vector<function<void()>>> ControllerListener::event_callback;
//map<Uint32, vector<function<void()>>> JoystickListener::event_callback;
//map<Uint32, vector<function<void()>>> FingerListener::event_callback;

IEventListener::IEventListener()
{

}

SDL_Event * IEventListener::getEvent()
{
    return this->event;
}

void IEventListener::registerEvent(Uint32 code, function<void()> callback)
{
    event_callback[code].push_back(callback);
}

void IEventListener::callEvent(Uint32 code)
{
    for(auto call : event_callback[code])
    {
        call();
    }
}

IEventListener::~IEventListener()
{

}

WindowListener::WindowListener()
{

}

WindowListener::~WindowListener()
{

}

KeyboardListener::KeyboardListener()
{

}

//void KeyboardListener::registerEvent(Uint32 code, function<void()> callback)
//{
//    event_callback[code].push_back(callback);
//}
//
//void KeyboardListener::callEvent(Uint32 code)
//{
//    for(auto call : event_callback[code])
//    {
//        call();
//    }
//}

KeyboardListener::~KeyboardListener()
{

}

MouseListener::MouseListener()
{

}

MouseListener::~MouseListener()
{

}

ControllerListener::ControllerListener()
{

}

ControllerListener::~ControllerListener()
{

}

JoystickListener::JoystickListener()
{

}

JoystickListener::~JoystickListener()
{

}

FingerListener::FingerListener()
{

}

FingerListener::~FingerListener()
{

}