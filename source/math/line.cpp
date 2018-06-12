#include "math/line.h"

namespace TURBO
{
    namespace MATH
    {
        Line::Line()
            : x1(0), y1(0), x2(0), y2(0)
        {

        }

        Line::Line(Point p1, Point p2)
            : x1(p1.x), y1(p1.y), x2(p2.x), y2(p2.y)
        {

        }

        Line::Line(Sint32 x1, Sint32 y1, Sint32 x2, Sint32 y2)
            : x1(x1), y1(y1), x2(x2), y2(y2)
        {

        }

        Point Line::first() const
        {
            return {x1, y1};
        }

        Point Line::second() const
        {
            return {x2, y2};
        }

        Line Line::operator+(const Line &other)
        {
            return {x1 + other.x1, y1 + other.y1, x2 + other.x2, y2 + other.y2};
        }

        Line &Line::operator+=(const Line &other)
        {
            x1 += other.x1;
            y1 += other.y1;
            x2 += other.x2;
            y2 += other.y2;
            return *this;
        }

        Line Line::operator-(const Line &other)
        {
            return {x1 - other.x1, y1 - other.y1, x2 - other.x2, y2 - other.y2};
        }

        Line &Line::operator-=(const Line &other)
        {
            x1 -= other.x1;
            y1 -= other.y1;
            x2 -= other.x2;
            y2 -= other.y2;
            return *this;
        }

        Line Line::operator*(const Line &other)
        {
            return {x1 * other.x1, y1 * other.y1, x2 * other.x2, y2 * other.y2};
        }

        Line &Line::operator*=(const Line &other)
        {
            x1 *= other.x1;
            y1 *= other.y1;
            x2 *= other.x2;
            y2 *= other.y2;
            return *this;
        }

        Line Line::operator/(const Line &other)
        {
            return {x1 / other.x1, y1 / other.y1, x2 / other.x2, y2 / other.y2};
        }

        Line &Line::operator/=(const Line &other)
        {
            x1 /= other.x1;
            y1 /= other.y1;
            x2 /= other.x2;
            y2 /= other.y2;
            return *this;
        }

        Line Line::operator*(Sint32 scalar)
        {
            return {x1 * scalar, y1 * scalar, x2 * scalar, y2 * scalar};
        }

        Line &Line::operator*=(Sint32 scalar)
        {
            x1 *= scalar;
            y1 *= scalar;
            x2 *= scalar;
            y2 *= scalar;
            return *this;
        }

        Line Line::operator/(Sint32 scalar)
        {
            return {x1 / scalar, y1 / scalar, x2 / scalar, y2 / scalar};
        }

        Line &Line::operator/=(Sint32 scalar)
        {
            x1 /= scalar;
            y1 /= scalar;
            x2 /= scalar;
            y2 /= scalar;
            return *this;
        }

        bool MATH::operator==(Line &first, Line &second)
        {
            return first.first() == second.first() && first.second() == second.second();
        }

        bool MATH::operator!=(Line &first, Line &second)
        {
            return !(first == second);
        }

        bool MATH::operator<(Line &first, Line &second)
        {
            return (first.first() < second.first()) && (first.second() < second.second());
        }

        bool MATH::operator<=(Line &first, Line &second)
        {
            return (first.first() <= second.first()) && (first.second() <= second.second());
        }

        bool MATH::operator>(Line &first, Line &second)
        {
            return (first.first() > second.first()) && (first.second() > second.second());
        }

        bool MATH::operator>=(Line &first, Line &second)
        {
            return (first.first() >= second.first()) && (first.second() >= second.second());
        }
    }
}