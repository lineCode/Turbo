#include "math/point.h"

namespace TURBO
{
    namespace MATH
    {
        Point::Point()
            : x(0), y(0), z(0)
        {

        }

        Point::Point(Sint32 x, Sint32 y, Sint32 z)
            : x(x), y(y), z(z)
        {

        }

        Point Point::operator+(const Point &other)
        {
            return {x + other.x, y + other.y, z + other.z};
        }

        Point& Point::operator+=(const Point &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Point Point::operator-(const Point &other)
        {
            return {x - other.x, y - other.y, z - other.z};
        }

        Point& Point::operator-=(const Point &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Point Point::operator*(const Point &other)
        {
            return {x * other.x, y * other.y, z * other.z};
        }

        Point& Point::operator*=(const Point &other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        Point Point::operator/(const Point &other)
        {
            return {x / other.x, y / other.y, z / other.z};
        }

        Point& Point::operator/=(const Point &other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        Point Point::operator*(Sint32 scalar)
        {
            return {x * scalar, y * scalar, z * scalar};
        }

        Point& Point::operator*=(Sint32 scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Point Point::operator/(Sint32 scalar)
        {
            return {x / scalar, y / scalar, z / scalar};
        }

        Point& Point::operator/=(Sint32 scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        Point Point::operator++(int)
        {
            Point result(*this);
            ++(*this);
            return result;
        }

        Point &Point::operator++()
        {
            x++;
            y++;
            z++;
            return *this;
        }

        Point Point::operator--(int)
        {
            Point result(*this);
            --(*this);
            return result;
        }

        Point &Point::operator--()
        {
            x--;
            y--;
            z--;
            return *this;
        }

        bool operator==(const Point &first, const Point &second)
        {
            return (first.x == second.x && first.y == second.y && first.z == second.z);
        }

        bool operator!=(const Point &first, const Point &second)
        {
            return !(first == second);
        }

        bool operator<(const Point &first, const Point &second)
        {
            return (first.x < second.x) && (first.y < second.y) && (first.z < second.z);
        }

        bool operator<=(const Point &first, const Point &second)
        {
            return (first.x <= second.x) && (first.y <= second.y) && (first.z <= second.z);
        }

        bool operator>(const Point &first, const Point &second)
        {
            return (first.x > second.x) && (first.y > second.y) && (first.z > second.z);
        }

        bool operator>=(const Point &first, const Point &second)
        {
            return (first.x >= second.x) && (first.y >= second.y) && (first.z >= second.z);
        }
    }
}