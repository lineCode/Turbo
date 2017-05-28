#include "turbo/application.h"
#include "turbo/default.h"

using namespace TURBO;
using UTILS::Log;
using GEOMETRY::Rectangle;

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
    : sdl(), timer(TURBO::TURBO_FPS_LOCK), settings(TURBO::TURBO_SETTINGSFILE),
      window(TURBO::APP_NAME, Rectangle(50, 50, 500, 400)), renderer(window),
      overlay(TURBO::APP_OVERLAY)
{
    this->registerEvent(SDL_QUIT, 0, std::bind(&Application::stop, this));
    this->registerEvent(SDL_KEYDOWN, SDLK_ESCAPE, std::bind(&Application::stop, this));
    //this->registerEvent(SDL_MOUSEBUTTONDOWN, std::bind(&Application::stop, this));
}

GUI::Window & Application::getWindow()
{
    return this->window;
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
                EVENT::IEventListener::callEvent(event.type, 0);
                break;
            }
        case SDL_WINDOWEVENT:
            {
                break;
            }
        case SDL_KEYDOWN: case SDL_KEYUP:
            {
                EVENT::IEventListener::callEvent(event.type, event.key.keysym.sym);
                break;
            }
        case SDL_JOYAXISMOTION:
            {
            
                break;
            }
        case SDL_JOYBUTTONDOWN: case SDL_JOYBUTTONUP:
            {
            
                break;
            }
        case SDL_MOUSEBUTTONDOWN: //case SDL_MOUSEBUTTONUP: case SDL_MOUSEMOTION:
            {
                //EVENT::IEventListener::callEvent(SDL_MOUSEBUTTONDOWN);
                break;
            }
        default:
            {

            }
        }
    }
}

void Application::gameLoop()
{
	
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
		this->gameLoop();
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