#include "video/surface.h"

namespace TURBO
{
    namespace VIDEO
    {
        Surface::Surface(std::string path, Renderer *renderer)
            : path(path)
        {
            surface = IMG_Load(path.c_str());

            if(surface != nullptr)
            {
                loadSurfaceInfo();
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
