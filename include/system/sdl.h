#ifndef TURBO_SDL_H
#define TURBO_SDL_H

#include "system/system_def.h"

namespace TURBO
{
    namespace SYSTEM
    {
        class SDL : SDL2pp::SDL
        {
        private:
            bool is_init = false;
            Uint32 init_flags = 0x0;

        public:
            explicit SDL(Uint32 sdl_flags);
        };

        class SDLImage : SDL2pp::SDLImage
        {
        private:
            bool is_init = false;
            Uint32 init_flags = 0x0;

        public:
            explicit SDLImage(Uint32 image_flags);
        };

        class SDLTTF : SDL2pp::SDLTTF
        {
        private:
            bool is_init = false;
            Uint32 init_flags = 0x0;

        public:
            SDLTTF();
        };

        class SDLMixer : SDL2pp::SDLMixer
        {
        private:
            bool is_init = false;
            Uint32 init_flags = 0x0;

        public:
            explicit SDLMixer(Uint32 mixer_flags);
        };

        class SDLNet
        {
        private:
            bool is_init = false;
            Uint32 init_flags = 0x0;

        public:
            SDLNet();
        };
    }
}

#endif //TURBO_SDL_H
