#ifndef TURBO_SDL_H
#define TURBO_SDL_H

#include "system/system_def.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_net.h"

namespace TURBO
{
    namespace SYSTEM
    {
        class SDL
        {
        private:
            bool is_init;
            Uint32 init_flags;

        public:
            explicit SDL(Uint32 flags);
            ~SDL();
        };

        class SDLIMG
        {
        private:
            bool is_init;
            Uint32 init_flags;

        public:
            explicit SDLIMG(Uint32 flags);
            ~SDLIMG();
        };

        class SDLTTF
        {
        private:
            bool is_init;

        public:
            SDLTTF();
            ~SDLTTF();
        };

        class SDLMIX
        {
        private:
            bool is_init;
            Uint32 init_flags;

        public:
            explicit SDLMIX(Uint32 flags);
            ~SDLMIX();
        };

        class SDLNET
        {
        private:
            bool is_init;

        public:
            SDLNET();
            ~SDLNET();
        };
    }
}

#endif //TURBO_SDL_H
