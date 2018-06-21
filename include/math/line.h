#ifndef TURBO_LINE_H
#define TURBO_LINE_H

#include "math/math_def.h"
#include "math/point.h"

namespace TURBO
{
    namespace MATH
    {
        class Line
        {
        public:
            Sint32 x1;
            Sint32 y1;
            Sint32 x2;
            Sint32 y2;

            Line();
            Line(Point p1, Point p2);
            Line(Sint32 x1, Sint32 y1, Sint32 x2, Sint32 y2);
            Point first() const;
            Point second() const;
            Line operator+(const Line &other);
            Line& operator+=(const Line &other);
            Line operator-(const Line &other);
            Line& operator-=(const Line &other);
            Line operator*(const Line &other);
            Line& operator*=(const Line &other);
            Line operator/(const Line &other);
            Line& operator/=(const Line &other);
            Line operator*(Sint32 scalar);
            Line& operator*=(Sint32 scalar);
            Line operator/(Sint32 scalar);
            Line& operator/=(Sint32 scalar);
            Line operator++(int);
            Line& operator++();
            Line operator--(int);
            Line& operator--();
            friend bool operator==(const Line &first, const Line &second);
            friend bool operator!=(const Line &first, const Line &second);
            friend bool operator<(const Line &first, const Line &second);
            friend bool operator<=(const Line &first, const Line &second);
            friend bool operator>(const Line &first, const Line &second);
            friend bool operator>=(const Line &first, const Line &second);
        };
    }
}

#endif //TURBO_LINE_H
