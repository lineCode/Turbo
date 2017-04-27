#include "turbo/application.h"
#include "turbo/default.h"

using namespace TURBO;
using UTILS::Log;

Settings::Settings(string file_path)
    : file_path(file_path)
{
    this->readSettings();
}

void Settings::setSetting(string key, string value, string caption)
{
    this->settings.setValue(caption, key, value);
}

string Settings::getSetting(string key, string caption)
{
    return this->settings.getValue(caption, key);
}

void Settings::initSettings()
{
    EXTERN::INI default_settings = Default::getDefaultSettings();

    for(auto cap : default_settings.kvp)
    {
        string caption = cap.first;
        for(auto kvp : cap.second)
        {
            string key = kvp.first;
            if(this->settings.kvp[caption][key] == "")
            {
                this->settings.kvp[caption][key] = default_settings.kvp[caption][key];
            }
        }
    }
}

void Settings::resetSettings()
{
    this->settings = Default::getDefaultSettings();
}

void Settings::writeSettings()
{
    EXTERN::INIParser parser(this->file_path, false);
    parser.write(this->file_path, this->settings);
}

void Settings::readSettings()
{
    EXTERN::INIParser parser(this->file_path);
    this->settings = parser.getINI();
}

Settings::~Settings()
{

}

Application::Application()
    : sdl(), timer(TURBO_FPS_LOCK), settings(TURBO_SETTINGSFILE), overlay()
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
    Uint64 start = this->timer.getTicks(), stop = 0;
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