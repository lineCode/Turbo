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

namespace LOGIC
{
    /**
    *** @class  ILogicObject
    ***
    *** @brief  ILogicObject is the base class for every object below the UI layout.
    **/
    class ILogicObject
    {
    private:
        const string TAG = "ILogicObject";

    protected:

    public:
        ILogicObject();
        ~ILogicObject();
    };

}

#endif // LOGIC_OBJECT_H_INCLUDED
