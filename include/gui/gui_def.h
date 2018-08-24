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
            ON_MOUSE_MOVING,
            ON_MOUSE_OUT,
            ON_MOUSE_BUTTON_DOWN,
            ON_MOUSE_BUTTON_UP,
            ON_POSITION_CHANGED,
            ON_SPACE_CHANGED,
            ON_SIZE_CHANGED,
            ON_CONTENT_CHANGED,
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
            TEXT_WIDGET,
            BUTTON,
            TEXT_INPUT,
        };

        enum class SIZE_POLICY : Uint8
        {
            MAXIMUM = 0x0,
            MINIMUM = 0x1
        };

        enum class SIZE_ADJUSTMENT : Uint8
        {
            ORIGINAL = 0x00,
            SCALED = 0x01
        };

        enum class ORIENTATION : Uint8
        {
            HORIZONTAL = 0x0,
            VERTICAL = 0x1
        };

        enum class ALIGNMENT : Uint8
        {
            LEFT          = 0x01,
            CENTER        = 0x02,
            RIGHT         = 0x03,
            TOP           = 0x10,
            MIDDLE        = 0x20,
            BOTTOM        = 0x30,
            TOP_LEFT      = 0x11,
            TOP_CENTER    = 0x12,
            TOP_RIGHT     = 0x13,
            MIDDLE_LEFT   = 0x21,
            MIDDLE_CENTER = 0x22,
            MIDDLE_RIGHT  = 0x23,
            BOTTOM_LEFT   = 0x31,
            BOTTOM_CENTER = 0x32,
            BOTTOM_RIGHT  = 0x33
        };
    }
}

#endif //TURBO_GUI_DEF_H
