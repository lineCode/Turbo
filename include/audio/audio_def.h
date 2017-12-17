#ifndef TURBO_AUDIO_DEF_H
#define TURBO_AUDIO_DEF_H

#include "turbo_def.h"

namespace TURBO
{
    namespace AUDIO
    {
        enum class PLAYER_STATE : Uint8
        {
            STOPPED = 0x0,
            PLAYING = 0x1,
            PAUSED  = 0x2,
        };
    }
}

#endif //TURBO_AUDIO_DEF_H
