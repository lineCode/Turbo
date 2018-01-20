#ifndef TURBO_GUI_DEF_H
#define TURBO_GUI_DEF_H

#include "turbo_def.h"

#include "video/renderer.h"
#include "video/texture.h"

namespace TURBO
{
    namespace GUI
    {
        enum EVENT_TYPE : Uint8
        {
            ON_MOUSE_OVER = 0x0,
            ON_MOUSE_OUT,
            ON_MOUSE_BUTTON_DOWN,
            ON_MOUSE_BUTTON_UP,
            ON_GEOMETRY_CHANGED,
            ON_SIZE_CHANGED,
            ON_VISIBILITY_CHANGED,
            ON_PARENT_CHANGED,
            ON_CHILD_CHANGED,
            ON_TEXT_CHANGED,
        };

        enum OBJECT_TYPE : Uint8
        {
            OBJECT = 0x0,
            LAYOUT,
            WIDGET,
            BUTTON,
            TEXT_INPUT,
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
