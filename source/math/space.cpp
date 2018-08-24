#include "math/space.h"

namespace TURBO
{
    namespace MATH
    {
        Space::Space()
            : top(0), right(0), bottom(0), left(0)
        {

        }

        Space::Space(Uint32 top, Uint32 right, Uint32 bottom, Uint32 left)
            : top(top), right(right), bottom(bottom), left(left)
        {

        }

        void Space::setSpace(Uint32 top, Uint32 right, Uint32 bottom, Uint32 left)
        {
            this->top    = top;
            this->right  = right;
            this->bottom = bottom;
            this->left   = left;
        }
    }
}