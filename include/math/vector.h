#ifndef TURBO_VECTOR_H
#define TURBO_VECTOR_H

#include "math/math_def.h"

namespace TURBO
{
    namespace MATH
    {
        class Vector
        {
        public:
            float x;
            float y;
            float z;

            Vector(float x, float y, float z);
        };
    }
}

#endif //TURBO_VECTOR_H
