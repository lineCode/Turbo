#ifndef TURBO_POINT_H
#define TURBO_POINT_H

typedef int Uint32;

namespace TURBO
{
    namespace MATH
    {
        class Point
        {
        public:
            Uint32 x;
            Uint32 y;
            Uint32 z;

            Point();
            Point(Uint32 x, Uint32 y, Uint32 z);
            Point& operator+(Point &other);
            Point& operator+=(Point &other);
            Point& operator-(Point &other);
            Point& operator-=(Point &other);
            Point& operator*(Point &other);
            Point& operator*=(Point &other);
            Point& operator/(Point &other);
            Point& operator/=(Point &other);
            Point& operator*(Uint32 scalar);
            Point& operator*=(Uint32 scalar);
            Point& operator/(Uint32 scalar);
            Point& operator/=(Uint32 scalar);
            friend bool operator==(Point & first, Point &second);
            friend bool operator!=(Point & first, Point &second);
        };
    }
}

#endif //TURBO_POINT_H
