#ifndef TURBO_GUI_DEF_H
#define TURBO_GUI_DEF_H

#include "turbo_def.h"

namespace TURBO
{
    namespace GUI
    {
        enum class EVENT_TYPE : Uint8
        {
            TURBO_ON_MOUSE_OVER = 0x0,
            TURBO_ON_MOUSE_OUT,
            TURBO_ON_MOUSE_DOWN,
            TURBO_ON_MOUSE_UP,
        };
    }
}

#endif //TURBO_GUI_DEF_H
