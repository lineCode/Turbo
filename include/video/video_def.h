#ifndef TURBO_VIDEO_DEF_H
#define TURBO_VIDEO_DEF_H

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "turbo_def.h"

namespace TURBO
{
    namespace VIDEO
    {
        enum class TEXT_MODE : Uint8
        {
            SOLID = 0x0,
            BLENDED = 0x1,
            SHADED = 0x2
        };
    }
}

#endif //TURBO_VIDEO_DEF_H
