#include "math/rect.h"

namespace TURBO
{
    namespace MATH
    {
        Rect::Rect()
            : x(0), y(0), w(0), h(0)
        {

        }

        Rect::Rect(Uint32 x, Uint32 y, Uint32 w, Uint32 h)
            : x(x), y(y), w(w), h(h)
        {

        }

        Rect &Rect::operator*(Uint32 scalar)
        {
            w *= scalar;
            h *= scalar;
            return *this;
        }

        Rect &Rect::operator/(Uint32 scalar)
        {
            w /= scalar;
            h /= scalar;
            return *this;
        }
    }
}