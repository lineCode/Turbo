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
        const string    TAG = "Application";

    protected:
        SYSTEM::SDL     sdl;

    public:
        Application();
        unsigned int    run();
        ~Application();
    };

}

#endif // APPLICATION_H_INCLUDED
