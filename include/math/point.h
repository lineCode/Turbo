#ifndef TURBO_POINT_H
#define TURBO_POINT_H

#include <SDL_types.h>

#include "math/math_def.h"

namespace TURBO
{
    namespace MATH
    {
        class Rect;

        class Point
        {
        public:
            Sint32 x;
            Sint32 y;
            Sint32 z;

            Point();
            Point(Sint32 x, Sint32 y);
            Point(Sint32 x, Sint32 y, Sint32 z);
        };
    }
}

#endif //TURBO_POINT_H
