#ifndef DEFAULT_H_INCLUDED
#define DEFAULT_H_INCLUDED

/**
*** @package 	default
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
    *** @class  Default
    ***
    *** @brief
    **/
    class Default
    {
    private:
        const string TAG = "Default";

    protected:

    public:
        Default();
        static EXTERN::INI getDefaultSettings();
        ~Default();
    };

}

#endif // DEFAULT_H_INCLUDED
