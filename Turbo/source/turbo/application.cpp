#include "turbo/application.h"

using namespace TURBO;
using UTILS::Log;

Settings::Settings(string file_path)
{

}

Settings::~Settings()
{

}

Application::Application()
    : sdl(), timer(TURBO_FPS_LOCK), settings()
{

}

void Application::eventLoop()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            {
                this->stop();
                break;
            }
        case SDL_WINDOWEVENT:
            {
                break;
            }
        case SDL_KEYDOWN: case SDL_KEYUP:
            {
                break;
            }
        case SDL_JOYAXISMOTION: case SDL_JOYBUTTONDOWN: case SDL_JOYBUTTONUP:
            {
                break;
            }
        case SDL_MOUSEMOTION: case SDL_MOUSEBUTTONDOWN: case SDL_MOUSEBUTTONUP:
            {
                break;
            }
        default:
            {

            }
        }
    }
}

void Application::registerCallbacks()
{

}

void Application::mainLoop()
{
    long start = this->timer.getTicks(), stop = 0;
    while(this->running)
    {
        this->eventLoop();
        stop = timer.getTicks();
        this->timer.calcDelay(start, stop);
        start = stop;
    }
}

unsigned int Application::run()
{
    this->mainLoop();
    return 0;
}

void Application::stop()
{
    this->running = false;
}

Application::~Application()
{

}