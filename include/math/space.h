#ifndef TURBO_SPACE_H
#define TURBO_SPACE_H

#include "math/math_def.h"

namespace TURBO
{
    namespace MATH
    {
        struct Space
        {
            Uint32 top;
            Uint32 right;
            Uint32 bottom;
            Uint32 left;

            Space();

            Space(Uint32 top, Uint32 right, Uint32 bottom, Uint32 left);

            void setSpace(Uint32 top, Uint32 right, Uint32 bottom, Uint32 left);
        };
    }
}

#endif //TURBO_SPACE_H
