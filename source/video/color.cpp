#include "video/color.h"

namespace TURBO
{
    namespace VIDEO
    {
        Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
            : r(r), g(g), b(b), a(a)
        {

        }

        Color::Color(float r, float g, float b, float a)
            : rf(r), gf(g), bf(b), af(a)
        {

        }

        SDL_Color Color::toSDLColor()
        {
            return {r, g, b, a};
        }
    }
}