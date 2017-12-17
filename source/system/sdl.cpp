#include "system/sdl.h"

namespace TURBO
{
    namespace SYSTEM
    {
        bool SDL::is_init = false;
        bool SDLIMG::is_init = false;
        bool SDLTTF::is_init = false;
        bool SDLMIX::is_init = false;
        bool SDLNET::is_init = false;

        SDL::SDL(Uint32 sdl_flags)
            : SDL2pp::SDL(sdl_flags), init_flags(sdl_flags)
        {
            SDL::is_init = true;
        }

        SDLIMG::SDLIMG(Uint32 image_flags)
            : SDL2pp::SDLImage(image_flags), init_flags(image_flags)
        {
            SDLIMG::is_init = true;
        }

        SDLTTF::SDLTTF()
            : SDL2pp::SDLTTF()
        {
            SDLTTF::is_init = true;
        }

        SDLMIX::SDLMIX(Uint32 mixer_flags)
            : SDL2pp::SDLMixer(mixer_flags), init_flags(mixer_flags)
        {
            SDLMIX::is_init = true;
        }

        SDLNET::SDLNET()
        {
            SDLNET::is_init = true;
        }
    }
}