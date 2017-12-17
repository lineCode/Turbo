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
            Uint32 init_flags = 0x0;

        public:
            static bool is_init;
            explicit SDL(Uint32 sdl_flags);
        };

        class SDLIMG : SDL2pp::SDLImage
        {
        private:
            Uint32 init_flags = 0x0;

        public:
            static bool is_init;
            explicit SDLIMG(Uint32 image_flags);
        };

        class SDLTTF : SDL2pp::SDLTTF
        {
        public:
            static bool is_init;
            SDLTTF();
        };

        class SDLMIX : SDL2pp::SDLMixer
        {
        private:
            Uint32 init_flags = 0x0;

        public:
            static bool is_init;
            explicit SDLMIX(Uint32 mixer_flags);
        };

        class SDLNET
        {
        public:
            static bool is_init;
            SDLNET();
        };
    }
}

#endif //TURBO_SDL_H
