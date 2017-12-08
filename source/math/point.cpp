#include "math/point.h"

namespace TURBO
{
    namespace MATH
    {
        Point::Point()
            : x(0), y(0), z(0)
        {

        }

        Point::Point(Uint32 x, Uint32 y, Uint32 z)
            : x(x), y(y), z(z)
        {

        }

        Point& Point::operator+(Point &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Point& Point::operator+=(Point &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Point& Point::operator-(Point &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Point& Point::operator-=(Point &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Point& Point::operator*(Point &other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        Point& Point::operator*=(Point &other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        Point& Point::operator/(Point &other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        Point& Point::operator/=(Point &other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        Point& Point::operator*(Uint32 scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Point& Point::operator*=(Uint32 scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Point& Point::operator/(Uint32 scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        Point& Point::operator/=(Uint32 scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        bool operator==(Point &first, Point &second)
        {
            return (first.x == second.x && first.y == second.y && first.z == second.z);
        }

        bool operator!=(Point &p, Point &q)
        {
            return !(p == q);
        }
    }
}