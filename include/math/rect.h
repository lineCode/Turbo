#ifndef TURBO_RECT_H
#define TURBO_RECT_H

typedef int Uint32;

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
            Rect& operator*(Uint32 scalar);
            Rect& operator/(Uint32 scalar);
        };
    }
}

#endif //TURBO_RECT_H
