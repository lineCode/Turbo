#ifndef TURBO_MATH_H
#define TURBO_MATH_H

#include "math/vector.h"
#include "math/point.h"
#include "math/rect.h"

namespace TURBO
{
    namespace MATH
    {
        bool pointInRect(Point &p, Rect &r);
    }
}

#endif //TURBO_MATH_H
