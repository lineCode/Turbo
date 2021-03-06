#ifndef TURBO_TURBO_H
#define TURBO_TURBO_H

#include "system/system.h"
#include "script/script.h"
#include "input/input.h"
#include "math/math.h"
#include "net/net.h"
#include "video/video.h"
#include "gui/gui.h"
#include "chart/chart.h"
#include "audio/audio.h"
#include "util/util.h"

namespace TURBO
{
    class Settings final
    {
    public:
        static Uint32 SDL_INIT_FLAGS;
        static Uint32 IMG_INIT_FLAGS;
        static Uint32 MIX_INIT_FLAGS;

        static Uint8 TURBO_FRAME_LIMIT;
    };
}

#endif //TURBO_TURBO_H
