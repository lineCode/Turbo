#include "math/rect.h"

namespace TURBO
{
    namespace MATH
    {
        Rect::Rect()
            : x(0), y(0), w(0), h(0)
        {

        }

        Rect::Rect(Sint32 x, Sint32 y, Sint32 w, Sint32 h)
            : x(x), y(y), w(w), h(h)
        {

        }

        Rect &Rect::add(Sint32 x, Sint32 y, Sint32 w, Sint32 h)
        {
            this->x += x;
            this->y += y;
            this->w += w;
            this->h += h;
        }

        Rect &Rect::sub(Sint32 x, Sint32 y, Sint32 w, Sint32 h)
        {
            this->x -= x;
            this->y -= y;
            this->w -= w;
            this->h -= h;
        }

        Rect &Rect::mul(Sint32 x, Sint32 y, Sint32 w, Sint32 h)
        {
            this->x *= x;
            this->y *= y;
            this->w *= w;
            this->h *= h;
        }

        Rect &Rect::div(Sint32 x, Sint32 y, Sint32 w, Sint32 h)
        {
            this->x /= (x != 0) ? x : 1;
            this->y /= (y != 0) ? y : 1;
            this->w /= (w != 0) ? w : 1;
            this->h /= (h != 0) ? h : 1;
        }

        Point Rect::topLeft() const
        {
            return {x, y};
        }

        Point Rect::topRight() const
        {
            return {x + w, y};
        }

        Point Rect::bottomLeft() const
        {
            return {x, y + h};
        }

        Point Rect::bottomRight() const
        {
            return {x + w, y + h};
        }

        Point Rect::center() const
        {
            return bottomRight() / 2;
        }

        Rect Rect::operator+(const Rect &other)
        {
            return {x + other.x, y + other.y, w + other.w, h + other.h};
        }

        Rect &Rect::operator+=(const Rect &other)
        {
            x += other.x;
            y += other.y;
            w += other.w;
            h += other.h;
            return *this;
        }

        Rect Rect::operator-(const Rect &other)
        {
            return {x - other.x, y - other.y, w - other.w, h - other.h};
        }

        Rect &Rect::operator-=(const Rect &other)
        {
            x -= other.x;
            y -= other.y;
            w -= other.w;
            h -= other.h;
            return *this;
        }

        Rect Rect::operator*(const Rect &other)
        {
            return {x * other.x, 
                    y * other.y, 
                    w * other.w, 
                    h * other.h};
        }

        Rect &Rect::operator*=(const Rect &other)
        {
            x *= other.x;
            y *= other.y;
            w *= other.w;
            h *= other.h;
            return *this;
        }

        Rect Rect::operator/(const Rect &other)
        {
            return {x / (other.x != 0) ? other.x : 1,
                    y / (other.y != 0) ? other.y : 1,
                    w / (other.w != 0) ? other.w : 1,
                    h / (other.h != 0) ? other.h : 1};
        }

        Rect &Rect::operator/=(const Rect &other)
        {
            x /= (other.x != 0) ? other.x : 1;
            y /= (other.y != 0) ? other.y : 1;
            w /= (other.w != 0) ? other.w : 1;
            h /= (other.h != 0) ? other.h : 1;
            return *this;
        }

        Rect Rect::operator*(Sint32 scalar)
        {
            return {x * (scalar != 0) ? scalar : 1,
                    y * (scalar != 0) ? scalar : 1,
                    w * (scalar != 0) ? scalar : 1,
                    h * (scalar != 0) ? scalar : 1};
        }

        Rect &Rect::operator*=(Sint32 scalar)
        {
            x *= (scalar != 0) ? scalar : 1;
            y *= (scalar != 0) ? scalar : 1;
            w *= (scalar != 0) ? scalar : 1;
            h *= (scalar != 0) ? scalar : 1;
            return *this;
        }

        Rect Rect::operator/(Sint32 scalar)
        {
            return {x / (scalar != 0) ? scalar : 1,
                    y / (scalar != 0) ? scalar : 1,
                    w / (scalar != 0) ? scalar : 1,
                    h / (scalar != 0) ? scalar : 1};
        }

        Rect &Rect::operator/=(Sint32 scalar)
        {
            x /= (scalar != 0) ? scalar : 1;
            y /= (scalar != 0) ? scalar : 1;
            w /= (scalar != 0) ? scalar : 1;
            h /= (scalar != 0) ? scalar : 1;
            return *this;
        }

        bool operator==(const Rect &first, const Rect &second)
        {
            return (first.x == second.x)
                && (first.y == second.y)
                && (first.w == second.w)
                && (first.h == second.h);

        }

        bool operator!=(const Rect &first, const Rect &second)
        {
            return !(first == second);
        }

        bool operator<(const Rect &first, const Rect &second)
        {
            Point tl1 = first.topLeft();
            Point tl2 = second.topLeft();
            Point br1 = first.bottomRight();
            Point br2 = second.bottomRight();

            return ((tl1 >= tl2) || (br1 <= br2))
                && (first.w < second.w)
                && (first.h < second.h);
        }

        bool operator<=(const Rect &first, const Rect &second)
        {
            Point tl1 = first.topLeft();
            Point tl2 = second.topLeft();
            Point br1 = first.bottomRight();
            Point br2 = second.bottomRight();

            return ((tl1 >= tl2) || (br1 <= br2))
                && (first.w <= second.w)
                && (first.h <= second.h);
        }

        bool operator>(const Rect &first, const Rect &second)
        {
            Point tl1 = first.topLeft();
            Point tl2 = second.topLeft();
            Point br1 = first.bottomRight();
            Point br2 = second.bottomRight();

            return ((tl1 <= tl2) || (br1 >= br2))
                   && (first.w > second.w)
                   && (first.h > second.h);
        }

        bool operator>=(const Rect &first, const Rect &second)
        {
            Point tl1 = first.topLeft();
            Point tl2 = second.topLeft();
            Point br1 = first.bottomRight();
            Point br2 = second.bottomRight();

            return ((tl1 <= tl2) || (br1 >= br2))
                   && (first.w >= second.w)
                   && (first.h >= second.h);
        }

        void Rect::registerToLuaScript(lua_State *state)
        {
            luabridge::getGlobalNamespace(state)
                .beginNamespace("MATH")
                    .beginClass<MATH::Rect>("Rect")
                    .addConstructor<void(*)(int, int, int, int)>()
                    .endClass()
                .endNamespace();
        }
    }
}