#include "math/point.h"

namespace TURBO
{
    namespace MATH
    {
        Point::Point()
            : x(0), y(0), z(0)
        {

        }

        Point::Point(Sint32 x, Sint32 y)
            : x(x), y(y), z(0)
        {

        }

        Point::Point(Sint32 x, Sint32 y, Sint32 z)
            : x(x), y(y), z(z)
        {

        }
    }
}