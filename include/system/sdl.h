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
            Uint32 sdl_flags;
            Uint32 image_flags;
            Uint32 mixer_flags;

        public:
            static bool SDL_IS_INIT;
            static bool OPENGL_IS_INIT;
            static bool IMG_IS_INIT;
            static bool MIX_IS_INIT;
            static bool TTF_IS_INIT;
            static bool NET_IS_INIT;

            SDL() = default;
            explicit SDL(Uint32 flags);
            static std::string getBasePath();
            static std::string createPrefPath(std::string prefix, std::string dirname);
            static std::string getRevision();
            static std::string getVersion();
            Uint32 initSDL(Uint32 flags);
            Uint32 initIMG(Uint32 flags);
            Uint32 initMIX(Uint32 flags);
            Uint32 initTTF();
            Uint32 initNET();
            void quitSDL();
            void quitIMG();
            void quitMIX();
            void quitTTF();
            void quitNET();
            ~SDL();
        };
    }
}

#endif //TURBO_SDL_H
