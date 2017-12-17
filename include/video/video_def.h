#ifndef TURBO_VIDEO_DEF_H
#define TURBO_VIDEO_DEF_H

#include <SDL_types.h>

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
