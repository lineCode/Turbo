#ifndef TURBO_COLOR_H
#define TURBO_COLOR_H

#include <SDL2pp/Color.hh>

#include "video/video_def.h"

namespace TURBO
{
    namespace VIDEO
    {
        class Color : public SDL2pp::Color
        {
        public:
            float rf;
            Uint8 r;
            float gf;
            Uint8 g;
            float bf;
            Uint8 b;
            float af;
            Uint8 a;

            Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
            Color(float r, float g, float b, float a);
            SDL_Color toSDLColor();
        };
    }
}

#endif //TURBO_COLOR_H
