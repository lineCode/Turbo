#ifndef TURBO_POINT_H
#define TURBO_POINT_H

#include "math/math_def.h"

namespace TURBO
{
    namespace MATH
    {
        class Point
        {
        public:
            Sint32 x;
            Sint32 y;
            Sint32 z;

            Point();
            Point(Sint32 x, Sint32 y, Sint32 z = 0);
            Point operator+(const Point &other);
            Point& operator+=(const Point &other);
            Point operator-(const Point &other);
            Point& operator-=(const Point &other);
            Point operator*(const Point &other);
            Point& operator*=(const Point &other);
            Point operator/(const Point &other);
            Point& operator/=(const Point &other);
            Point operator*(Sint32 scalar);
            Point& operator*=(Sint32 scalar);
            Point operator/(Sint32 scalar);
            Point& operator/=(Sint32 scalar);
            Point operator++(int);
            Point& operator++();
            Point operator--(int);
            Point& operator--();
            friend bool operator==(const Point &first, const Point &second);
            friend bool operator!=(const Point &first, const Point &second);
            friend bool operator<(const Point &first, const Point &second);
            friend bool operator<=(const Point &first, const Point &second);
            friend bool operator>(const Point &first, const Point &second);
            friend bool operator>=(const Point &first, const Point &second);
        };
    }
}

#endif //TURBO_POINT_H
