#ifndef TURBO_MATH_H
#define TURBO_MATH_H

#include "math/range.h"
#include "math/point.h"
#include "math/line.h"
#include "math/rect.h"
#include "math/vector.h"
#include "math/space.h"

namespace TURBO
{
    namespace MATH
    {
        bool pointInRect(Point &p, Rect &r);
    }
}

#endif //TURBO_MATH_H
