#ifndef TURBO_LUA_POINT_H
#define TURBO_LUA_POINT_H

#include "script/lua_def.h"

namespace TURBO
{
    namespace SCRIPT
    {
        class LuaPoint : LuaObject<LuaPoint>
        {
        public:
            int x;
            int y;

            explicit LuaPoint(int x = 0, int y = 0)
                : x(x), y(y)
            {

            }

            static int __new(lua_State * L)
            {
                auto x = (int)luaL_checknumber(L, -2);
                auto y = (int)luaL_checknumber(L, -1);

                /* stack:
                 * NUMBER       | y
                 * NUMBER       | x
                 */

                auto data = (LuaPoint **)lua_newuserdata(L, sizeof(LuaPoint *));
                *data = new LuaPoint(x, y);

                /* stack:
                 * USERDATA
                 * NUMBER       | y
                 * NUMBER       | x
                 */

                std::string metatable_name = "LUA_" + UTIL::rawTypeName<LuaPoint>();
                luaL_getmetatable(L, metatable_name.c_str());

                /* stack:
                 * METATABLE
                 * USERDATA
                 * NUMBER       | y
                 * NUMBER       | x
                 */

                lua_setmetatable(L, -2);

                /* stack:
                 * USERDATA
                 * NUMBER       | y
                 * NUMBER       | x
                 */

                return 1;
            }

            static int get(lua_State * L)
            {
                auto p = checkUserData(L, 1);

                lua_pushnumber(L, p->x);
                lua_pushnumber(L, p->y);

                /* stack:
                 * NUMBER       | y
                 * NUMBER       | x
                 * METATABLE
                 * USERDATA
                 */

                return 2;
            }

            static void Register(lua_State * L)
            {
                luaL_Reg methods_parent[] = {
                    {"new", LuaObject::__new},
                    {"__gc", LuaObject::__delete},
                    {nullptr, nullptr}
                };

                luaL_Reg methods[] = {
                    {"new", LuaPoint::__new},
                    {"get", LuaPoint::get},
                    {"__gc", LuaObject::__delete},
                    {nullptr, nullptr}
                };

                std::string class_name = getClassName();
                std::string metatable_name = "LUA_" + class_name;
                luaL_newmetatable(L, metatable_name.c_str());

                /* stack:
                 * METATABLE
                 */

                // inherited default methods
                luaL_setfuncs (L, methods_parent, 0);

                // overwrite or add methods
                luaL_setfuncs (L, methods, 0);
                lua_pushvalue(L, -1);

                /* stack:
                 * METATABLE
                 * METATABLE
                 */

                lua_setfield(L, -1, "__index");

                /* stack:
                 * METATABLE
                 */

                lua_setglobal(L, class_name.c_str());
            }
        };
    }
}

#endif //TURBO_LUA_POINT_H
