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
        const std::string TAG = "Settings";

        std::string file_path;
        EXTERN::INI settings;

    protected:

    public:
        Settings(string file_path);
        void        setSetting(std::string key, std::string value, std::string caption = "");
        std::string getSetting(std::string key, std::string caption = "");
        void        initSettings();
        void        resetSettings();
        void        writeSettings();
        void        readSettings();
        ~Settings();
    };


    /**
    *** @class Application
    ***
    *** @var
    **/
    class Application : public EVENT::IEventListener
    {
    private:
        const std::string        TAG = "Application";

    protected:
        SYSTEM::SDL         sdl;
        EXTERN::AppTimer    timer;
        Settings            settings;
        GUI::Window         window;
        GUI::IRenderer      renderer;
        GUI::Overlay        overlay;
        bool                running = true;

    public:
        Application();
        GUI::Window       & getWindow();
        void                eventLoop();
		void                gameLoop();
        void                registerCallbacks();
        void                mainLoop();
        unsigned int        run();
        void                stop();
        ~Application();
    };

}

#endif // APPLICATION_H_INCLUDED
