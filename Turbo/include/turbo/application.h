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
