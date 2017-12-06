#ifndef TURBO_TURBO_H
#define TURBO_TURBO_H

#include "system/system.h"
#include "script/script.h"
#include "input/input.h"
#include "math/math.h"
#include "video/video.h"
#include "gui/gui.h"
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
    };

    class Turbo
    {
    private:
        Uint8 frame_limit = 60;

    public:
        SYSTEM::SDL         sdl;
        SYSTEM::SDLImage    sdl_image;
        SYSTEM::SDLMixer    sdl_mixer;
        SYSTEM::SDLTTF      sdl_ttf;
        SYSTEM::SDLNet      sdl_net;

        explicit Turbo(Uint32 sdl_flags = SDL_INIT_EVERYTHING);
        void setFrameLimit(Uint8 limit);
        Uint8 getFrameLimit();
        int run();
        ~Turbo();
    };
}

#endif //TURBO_TURBO_H
