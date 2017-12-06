#include "system/sdl.h"

namespace TURBO
{
    namespace SYSTEM
    {
        SDL::SDL(Uint32 sdl_flags)
            : SDL2pp::SDL(sdl_flags)
        {

        }

        SDLImage::SDLImage(Uint32 image_flags)
            : SDL2pp::SDLImage(image_flags)
        {

        }

        SDLTTF::SDLTTF()
            : SDL2pp::SDLTTF()
        {

        }

        SDLMixer::SDLMixer(Uint32 mixer_flags)
            : SDL2pp::SDLMixer(mixer_flags)
        {

        }

        SDLNet::SDLNet()
        {

        }
    }
}