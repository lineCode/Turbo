#ifndef TURBO_SURFACE_H
#define TURBO_SURFACE_H

#include "SDL_image.h"

#include "video/video_def.h"
#include "video/renderer.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Surface
        {
        private:
            std::string path;
            SDL_Surface *surface;
            Sint32 w;
            Sint32 h;

        public:
            Surface(std::string path, Renderer *renderer);
            void loadSurfaceInfo();
        };
    }
}

#endif //TURBO_SURFACE_H