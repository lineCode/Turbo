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
    }
}