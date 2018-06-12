#ifndef TURBO_RECT_H
#define TURBO_RECT_H

#include <lua.hpp>
#include "script/LuaBridge/LuaBridge.h"

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
            Point topLeft();
            Point topRight();
            Point bottomLeft();
            Point bottomRight();
            Point center();
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
            friend bool operator==(Rect & first, Rect &second);
            friend bool operator!=(Rect & first, Rect &second);
            friend bool operator<(Rect & first, Rect &second);
            friend bool operator<=(Rect & first, Rect &second);
            friend bool operator>(Rect & first, Rect &second);
            friend bool operator>=(Rect & first, Rect &second);

            static void registerToLuaScript(lua_State *state);
        };
    }
}

#endif //TURBO_RECT_H
