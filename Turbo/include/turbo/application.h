#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

/**
*** @package 	application
*** @author		Christoph Zorn
*** @date		24.02.2017
***
*** @brief
***
***
**/

#include "Turbo.h"

namespace TURBO
{
    /**
    *** @class  Settings
    ***
    *** @brief  Represents all settings of created application
    **/
    class Settings
    {
    private:
        const string TAG = "Settings";

    protected:

    public:
        Settings(string file_path = TURBO::TURBO_SETTINGSFILE);
        ~Settings();
    };


    /**
    *** @class Application
    ***
    *** @var
    **/
    class Application
    {
    private:
        const string        TAG = "Application";

    protected:
        SYSTEM::SDL         sdl;
        EXTERN::AppTimer    timer;
        Settings            settings;
        GUI::IGUIObject     overlay;
        //GUI::Window         window;
        //GUI::IRenderer      renderer;
        bool                running = true;

    public:
        Application();
        void                eventLoop();
        void                registerCallbacks();
        void                mainLoop();
        unsigned int        run();
        void                stop();
        ~Application();
    };

}

#endif // APPLICATION_H_INCLUDED
