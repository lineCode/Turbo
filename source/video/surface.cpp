#include "video/surface.h"

namespace TURBO
{
    namespace VIDEO
    {
        Surface::Surface(std::string path, Renderer *renderer)
            : path(path)
        {
            if(SYSTEM::SDL::IMG_IS_INIT)
            {
                surface = IMG_Load(path.c_str());

                if(surface != nullptr)
                {
                    loadSurfaceInfo();
                }
            }
            else
            {
                UTIL::Log::err("SDL_IMG is not initialized");
            }
        }

        void Surface::loadSurfaceInfo()
        {
            if(surface != nullptr)
            {
                w = surface->w;
                h = surface->h;
            }
        }
    }
}
