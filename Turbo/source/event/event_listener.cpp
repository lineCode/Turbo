#include "event/event_listener.h"

using namespace EVENT;

IEventListener::IEventListener()
{

}

IEventListener::~IEventListener()
{

}

KeyboardListener::KeyboardListener()
{

}

void KeyboardListener::registerCallback(Uint32 code, std::function<void()> callback)
{
    this->callback[code].push_back(callback);
}

void KeyboardListener::callCallback(Uint32 code)
{
    for(auto call : this->callback[code])
    {
        call();
    }
}

KeyboardListener::~KeyboardListener()
{

}