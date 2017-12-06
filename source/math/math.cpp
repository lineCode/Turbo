#include "math/math.h"

namespace TURBO
{
    namespace MATH
    {
        bool pointInRect(Point &p, Rect &r)
        {
            if(p.x > r.x && p.x < r.x + r.w)
            {
                if(p.y > r.y && p.y < r.y + r.h)
                {
                    return true;
                }
            }
            return false;
        }
    }
}