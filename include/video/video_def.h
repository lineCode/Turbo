#ifndef TURBO_VIDEO_DEF_H
#define TURBO_VIDEO_DEF_H

#include <SDL_types.h>

#include "turbo_def.h"

namespace TURBO
{
    namespace VIDEO
    {
        const Uint32 TURBO_GL_MAJOR = 3;
        const Uint32 TURBO_GL_MINOR = 3;

        const Uint32 TURBO_SDL_TEXTURE_FORMAT = SDL_PIXELFORMAT_ARGB8888;
        const Uint32 TURBO_SDL_TEXTURE_ACCESS = SDL_TEXTUREACCESS_STATIC;
    }
}

#endif //TURBO_VIDEO_DEF_H
