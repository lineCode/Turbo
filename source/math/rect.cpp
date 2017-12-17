#include "math/rect.h"

namespace TURBO
{
    namespace MATH
    {
        Rect::Rect()
            : x(0), y(0), w(0), h(0)
        {

        }

        Rect::Rect(Sint32 x, Sint32 y, Sint32 w, Sint32 h)
            : x(x), y(y), w(w), h(h)
        {

        }

        Point Rect::topLeft()
        {
            return {x, y};
        }

        Point Rect::topRight()
        {
            return {x + w, y};
        }

        Point Rect::bottomLeft()
        {
            return {x, y +h};
        }

        Point Rect::bottomRight()
        {
            return {x + w, y + h};
        }

        Point Rect::center()
        {
            return bottomRight() / 2;
        }

        Rect &Rect::operator*(Sint32 scalar)
        {
            w *= scalar;
            h *= scalar;
            return *this;
        }

        Rect &Rect::operator/(Sint32 scalar)
        {
            w /= scalar;
            h /= scalar;
            return *this;
        }

        bool operator==(Rect &first, Rect &second)
        {
            return (first.x == second.x)
                && (first.y == second.y)
                && (first.w == second.w)
                && (first.h == second.h);

        }

        bool operator!=(Rect &first, Rect &second)
        {
            return !(first == second);
        }

        bool operator<(Rect &first, Rect &second)
        {
            Point tl1 = first.topLeft();
            Point tl2 = first.topLeft();
            Point br1 = first.bottomRight();
            Point br2 = first.bottomRight();

            return (first.w < second.w)
                && (first.h < second.h)
                && ((tl1 >= tl2) || (br1 <= br2));
        }

        bool operator<=(Rect &first, Rect &second)
        {
            return (first < second) || (first == second);
        }
    }
}