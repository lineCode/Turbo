#ifndef ACTORS_H_INCLUDED
#define ACTORS_H_INCLUDED

#include "logic.h"

namespace LOGIC
{
    /**
    *** @enum   ACTOR_TYPE
    ***
    *** @brief
    **/
    enum class ACTOR_TYPE : Uint8
    {
        NPC         = 0,
        PLAYER      = 1
    };

    /**
    *** @class  IActor
    ***
    *** @brief
    **/
    class IActor
    {
    private:
        const std::string TAG = "IActor";

    protected:

    public:
        IActor();
        ~IActor();
    };



}

#endif // ACTORS_H_INCLUDED
