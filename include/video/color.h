#ifndef Uint8URBO_COLOR_H
#define Uint8URBO_COLOR_H

#include <SDL2pp/Color.hh>

#include "video/video_def.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Color
        {
        public:
            Uint8 r;
            Uint8 g;
            Uint8 b;
            Uint8 a;

            Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
            SDL_Color toSDLColor();
        };
    }
}

#endif //Uint8URBO_COLOR_H
