#ifndef LOGIC_OBJECT_H_INCLUDED
#define LOGIC_OBJECT_H_INCLUDED

/**
*** @package    logic_object
*** @author		Christoph Zorn
*** @date		24.02.2017
***
*** @brief		The logic_object module contains
***
***
**/

#include "logic.h"

namespace LOGIC
{
    /**
    *** @enum   OBJECT_TYPE
    ***
    *** @brief
    **/
    enum class OBJECT_TYPE : Uint8
    {
        STATIC = 0
    };

    /**
    *** @class  ILogicObject
    ***
    *** @brief  ILogicObject is the base class for every object below the UI layout.
    **/
    class ILogicObject
    {
    private:
        const std::string TAG = "ILogicObject";

    protected:

    public:
        ILogicObject();
        ~ILogicObject();
    };

}

#endif // LOGIC_OBJECT_H_INCLUDED
