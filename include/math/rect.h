#ifndef TURBO_RECT_H
#define TURBO_RECT_H

#include "math/math_def.h"
#include "math/point.h"

namespace TURBO
{
    namespace MATH
    {
        class Rect
        {
        public:
            Sint32 x;
            Sint32 y;
            Sint32 w;
            Sint32 h;

            Rect();
            Rect(Sint32 x, Sint32 y, Sint32 w, Sint32 h);
            Point topLeft();
            Point topRight();
            Point bottomLeft();
            Point bottomRight();
            Point center();
            Rect& operator*(Sint32 scalar);
            Rect& operator/(Sint32 scalar);
            friend bool operator==(Rect & first, Rect &second);
            friend bool operator!=(Rect & first, Rect &second);
            friend bool operator<(Rect & first, Rect &second);
            friend bool operator<=(Rect & first, Rect &second);
        };
    }
}

#endif //TURBO_RECT_H
