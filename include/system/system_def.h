#ifndef TURBO_SYSTEM_DEF_H
#define TURBO_SYSTEM_DEF_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_net.h>

#include "turbo_def.h"

namespace TURBO
{
    namespace SYSTEM
    {
        static bool SYSTEM_RUNNING = true;

        enum class TIMER_STATE : Uint8
        {
            STOPPED = 0x0,
            STARTED = 0x1,
            PAUSED  = 0x2
        };
    }
}

#endif //TURBO_SYSTEM_DEF_H
