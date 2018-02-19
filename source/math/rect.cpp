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
            this->x *= (x != 0) ? x : 1;
            this->y *= (y != 0) ? y : 1;
            this->w *= (w != 0) ? w : 1;
            this->h *= (h != 0) ? h : 1;
        }

        Rect &Rect::div(Sint32 x, Sint32 y, Sint32 w, Sint32 h)
        {
            this->x /= (x != 0) ? x : 1;
            this->y /= (y != 0) ? y : 1;
            this->w /= (w != 0) ? w : 1;
            this->h /= (h != 0) ? h : 1;
        }

        Point Rect::topLeft()
        {
            return {x, y};
        }

        Point Rect::topRight()
        {
            return {x + w, y};
        }

        Point Rect::bottomLeft()
        {
            return {x, y + h};
        }

        Point Rect::bottomRight()
        {
            return {x + w, y + h};
        }

        Point Rect::center()
        {
            return bottomRight() / 2;
        }

        Rect &Rect::operator*(Sint32 scalar)
        {
            w *= scalar;
            h *= scalar;
            return *this;
        }

        Rect &Rect::operator/(Sint32 scalar)
        {
            w /= scalar;
            h /= scalar;
            return *this;
        }

        bool operator==(Rect &first, Rect &second)
        {
            return (first.x == second.x)
                && (first.y == second.y)
                && (first.w == second.w)
                && (first.h == second.h);

        }

        bool operator!=(Rect &first, Rect &second)
        {
            return !(first == second);
        }

        bool operator<(Rect &first, Rect &second)
        {
            Point tl1 = first.topLeft();
            Point tl2 = second.topLeft();
            Point br1 = first.bottomRight();
            Point br2 = second.bottomRight();

            return ((tl1 >= tl2) || (br1 <= br2))
                && (first.w < second.w)
                && (first.h < second.h);
        }

        bool operator<=(Rect &first, Rect &second)
        {
            Point tl1 = first.topLeft();
            Point tl2 = second.topLeft();
            Point br1 = first.bottomRight();
            Point br2 = second.bottomRight();

            return ((tl1 >= tl2) || (br1 <= br2))
                && (first.w <= second.w)
                && (first.h <= second.h);
        }

        bool operator>(Rect &first, Rect &second)
        {
            Point tl1 = first.topLeft();
            Point tl2 = second.topLeft();
            Point br1 = first.bottomRight();
            Point br2 = second.bottomRight();

            return ((tl1 <= tl2) || (br1 >= br2))
                   && (first.w > second.w)
                   && (first.h > second.h);
        }

        bool operator>=(Rect &first, Rect &second)
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