#include "video/color.h"

namespace TURBO
{
    namespace VIDEO
    {
        Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
            : r(r), g(g), b(b), a(a)
        {

        }

        SDL_Color Color::toSDLColor()
        {
            return {r, g, b, a};
        }

        Uint32 Color::toHexColor()
        {
            Uint32 color = 0x00000000;
            color = (color + r) << 8;
            color = (color + g) << 8;
            color = (color + b) << 8;
            color += a;

            return color;
        }
    }
}