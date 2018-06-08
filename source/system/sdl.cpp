#include "system/sdl.h"

namespace TURBO
{
    namespace SYSTEM
    {
        bool SDL::SDL_IS_INIT = false;
        bool SDL::OPENGL_IS_INIT = false;
        bool SDL::IMG_IS_INIT = false;
        bool SDL::MIX_IS_INIT = false;
        bool SDL::TTF_IS_INIT = false;
        bool SDL::NET_IS_INIT = false;

        SDL::SDL(Uint32 flags)
        {
            initSDL(flags);
        }

        std::string SDL::getBasePath()
        {
            char * base_path = SDL_GetBasePath();
            return base_path;
        }

        std::string SDL::createPrefPath(std::string prefix, std::string dirname)
        {
            char * pref_path = SDL_GetPrefPath(prefix.c_str(), dirname.c_str());
            return pref_path;
        }

        std::string SDL::getRevision()
        {
            return SDL_GetRevision() + std::to_string(SDL_GetRevisionNumber());
        }

        std::string SDL::getVersion()
        {
            SDL_version * v = nullptr;
            SDL_GetVersion(v);
            Uint8 version = v->major;
            return "" + version;
        }

        Uint32 SDL::initSDL(Uint32 flags)
        {
            if(!SDL::SDL_IS_INIT)
            {
                if(SDL_Init(flags) == 0)
                {
                    sdl_flags |= flags;
                    SDL::SDL_IS_INIT = true;
                }
            }
            else
            {
                flags |= this->sdl_flags;
                if(SDL_InitSubSystem(flags) == 0)
                {
                    sdl_flags |= flags;
                }
            }
            return sdl_flags;
        }

        Uint32 SDL::initIMG(Uint32 flags)
        {
            if(!SDL::IMG_IS_INIT && SDL::SDL_IS_INIT)
            {
                if((IMG_Init(flags) & flags) == flags)
                {
                    image_flags |= flags;
                    SDL::IMG_IS_INIT = true;
                }
            }
            return image_flags;
        }

        Uint32 SDL::initMIX(Uint32 flags)
        {
            if(!SDL::MIX_IS_INIT && SDL::SDL_IS_INIT)
            {
                if((Mix_Init(flags) & flags) == flags)
                {
                    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

                    mixer_flags |= flags;
                    SDL::MIX_IS_INIT = true;
                }
            }
            return mixer_flags;
        }

        Uint32 SDL::initTTF()
        {
            if(!SDL::TTF_IS_INIT && SDL::SDL_IS_INIT)
            {
                if(TTF_Init() == 0)
                {
                    SDL::TTF_IS_INIT = true;
                    return 1;
                }
            }
            return 0;
        }

        Uint32 SDL::initNET()
        {
            if(!SDL::NET_IS_INIT && SDL::SDL_IS_INIT)
            {
                if(SDLNet_Init() == 0)
                {
                    SDL::NET_IS_INIT = true;
                    return 1;
                }
            }
            return 0;
        }

        void SDL::quitSDL()
        {
            if(SDL::SDL_IS_INIT)
            {
                SDL_Quit();
                SDL::SDL_IS_INIT = false;
            }
        }

        void SDL::quitIMG()
        {
            if(SDL::IMG_IS_INIT)
            {
                IMG_Quit();
                SDL::IMG_IS_INIT = false;
            }
        }

        void SDL::quitMIX()
        {
            if(SDL::MIX_IS_INIT)
            {
                Mix_CloseAudio();
                Mix_Quit();
                SDL::MIX_IS_INIT = false;
            }
        }

        void SDL::quitTTF()
        {
            if(SDL::TTF_IS_INIT)
            {
                TTF_Quit();
                SDL::TTF_IS_INIT = false;
            }
        }

        void SDL::quitNET()
        {
            if(SDL::NET_IS_INIT)
            {
                SDLNet_Quit();
                SDL::NET_IS_INIT = false;
            }
        }

        SDL::~SDL()
        {
            quitNET();
            quitTTF();
            quitMIX();
            quitIMG();
            quitSDL();
        }
    }
}