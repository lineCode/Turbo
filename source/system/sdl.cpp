#include "system/sdl.h"

namespace TURBO
{
    namespace SYSTEM
    {
        SDL::SDL(Uint32 flags)
        {
            if(!(flags & init_flags))
            {
                if(is_init)
                {
                    if(SDL_InitSubSystem(flags) > 0)
                    {
                        init_flags |= flags;
                    }
                }
                else
                {
                    if(SDL_Init(flags) > 0)
                    {
                        init_flags |= flags;
                        is_init = true;
                    }
                }
            }
        }

        SDL::~SDL()
        {
            SDL_Quit();
        }

        SDLIMG::SDLIMG(Uint32 flags)
        {
            if(!(flags & init_flags))
            {
                if(is_init)
                {
                    if(IMG_Init(flags) > 0)
                    {
                        init_flags |= flags;
                        is_init = true;
                    }
                }
            }
        }

        SDLIMG::~SDLIMG()
        {
            IMG_Quit();
            is_init = false;
        }

        SDLTTF::SDLTTF()
        {
            TTF_Init();
            is_init = true;
        }

        SDLTTF::~SDLTTF()
        {
            TTF_Quit();
            is_init = false;
        }

        SDLMIX::SDLMIX(Uint32 flags)
        {
            if(!(flags & init_flags))
            {
                if(is_init)
                {
                    if(Mix_Init(flags) > 0)
                    {
                        init_flags |= flags;
                        is_init = true;
                    }
                }
            }
        }

        SDLMIX::~SDLMIX()
        {
            Mix_Quit();
            is_init = false;
        }

        SDLNET::SDLNET()
        {
            SDLNet_Init();
            is_init = true;
        }

        SDLNET::~SDLNET()
        {
            SDLNet_Quit();
            is_init = false;
        }
    }
}