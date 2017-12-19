#ifndef TURBO_AUDIO_DEF_H
#define TURBO_AUDIO_DEF_H

#include "SDL_mixer.h"

#include "turbo_def.h"

namespace TURBO
{
    namespace AUDIO
    {
        const Uint8 MIN_VOLUME = 0;
        const Uint8 MAX_VOLUME = MIX_MAX_VOLUME;

        enum class MEDIUM_STATE : Uint8
        {
            STOPPED = 0x0,
            PLAYING = 0x1,
            PAUSED  = 0x2,
        };
    }
}

#endif //TURBO_AUDIO_DEF_H
