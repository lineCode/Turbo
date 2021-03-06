#ifndef TURBO_SURFACE_H
#define TURBO_SURFACE_H

#include "SDL_image.h"

#include "video/video_def.h"
#include "system/sdl.h"
#include "util/log.h"
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
            Sint32      w;
            Sint32      h;

        public:
            /**
             * Creates a surface.
             * @param path      the path to the image.
             * @param renderer  a pointer to the renderer
             */
            Surface(std::string path, Renderer *renderer);

            ~Surface();

            SDL_Surface *getSurface();

            /**
             * Reloads the surface informations.
             */
            void loadSurfaceInfo();
        };
    }
}

#endif //TURBO_SURFACE_H
