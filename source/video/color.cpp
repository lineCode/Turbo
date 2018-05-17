#include "video/color.h"

namespace TURBO
{
    namespace VIDEO
    {
        Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
            : r(r), g(g), b(b), a(a)
        {

        }

        Color::Color(Uint32 color)
        {
            r = static_cast<Uint8>((color >> 24) & 0xFF);
            g = static_cast<Uint8>((color >> 16) & 0xFF);
            b = static_cast<Uint8>((color >> 8) & 0xFF);
            a = static_cast<Uint8>(color & 0xFF);
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