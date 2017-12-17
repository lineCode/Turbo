#ifndef TURBO_GUI_DEF_H
#define TURBO_GUI_DEF_H

#include "turbo_def.h"

namespace TURBO
{
    namespace GUI
    {
        enum EVENT_TYPE : Uint8
        {
            ON_MOUSE_OVER = 0x0,
            ON_MOUSE_OUT,
            ON_MOUSE_BUTTON_DOWN,
            ON_MOUSE_BUTTON_UP
        };

        enum OBJECT_TYPE : Uint8
        {
            OBJECT = 0x0,
            LAYOUT = 0x1,
            WIDGET = 0x2
        };

        enum class SIZE_POLICY : Uint8
        {
            MAXIMUM = 0x0,
            MINIMUM = 0x1

        };

        enum class ORIENTATION : Uint8
        {
            HORIZONTAL = 0x0,
            VERTICAL = 0x1
        };
    }
}

#endif //TURBO_GUI_DEF_H
