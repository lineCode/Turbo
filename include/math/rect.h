#ifndef TURBO_RECT_H
#define TURBO_RECT_H

#include "math/math_def.h"
#include "math/point.h"

namespace TURBO
{
    namespace MATH
    {
        class Rect
        {
        public:
            Sint32 x;
            Sint32 y;
            Sint32 w;
            Sint32 h;

            Rect();
            Rect(Sint32 x, Sint32 y, Sint32 w, Sint32 h);
            Rect& add(Sint32 x, Sint32 y, Sint32 w, Sint32 h);
            Rect& sub(Sint32 x, Sint32 y, Sint32 w, Sint32 h);
            Rect& mul(Sint32 x, Sint32 y, Sint32 w, Sint32 h);
            Rect& div(Sint32 x, Sint32 y, Sint32 w, Sint32 h);
            Point topLeft() const;
            Point topRight() const;
            Point bottomLeft() const;
            Point bottomRight() const;
            Point center() const;
            Rect operator+(const Rect &other);
            Rect& operator+=(const Rect &other);
            Rect operator-(const Rect &other);
            Rect& operator-=(const Rect &other);
            Rect operator*(const Rect &other);
            Rect& operator*=(const Rect &other);
            Rect operator/(const Rect &other);
            Rect& operator/=(const Rect &other);
            Rect operator*(Sint32 scalar);
            Rect& operator*=(Sint32 scalar);
            Rect operator/(Sint32 scalar);
            Rect& operator/=(Sint32 scalar);
            static Rect& max(Rect &first, Rect &second);
            friend bool operator==(const Rect & first, const Rect &second);
            friend bool operator!=(const Rect & first, const Rect &second);
            friend bool operator<(const Rect & first, const Rect &second);
            friend bool operator<=(const Rect & first, const Rect &second);
            friend bool operator>(const Rect & first, const Rect &second);
            friend bool operator>=(const Rect & first, const Rect &second);
        };
    }
}

#endif //TURBO_RECT_H
