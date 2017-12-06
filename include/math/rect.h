#ifndef TURBO_RECT_H
#define TURBO_RECT_H

#include <SDL_types.h>

#include "math/math_def.h"

namespace TURBO
{
    namespace MATH
    {
        class Rect
        {
        public:
            Uint32 x;
            Uint32 y;
            Uint32 w;
            Uint32 h;

            Rect();
            Rect(Uint32 x, Uint32 y, Uint32 w, Uint32 h);
        };
    }
}

#endif //TURBO_RECT_H
