#ifndef TURBO_LUA_DEF_H
#define TURBO_LUA_DEF_H

#ifdef __cplusplus
    #include <lua.hpp>

#else
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
#endif

#include "script/script_def.h"
#include "util/type.h"

namespace TURBO
{
    namespace SCRIPT
    {
        template<typename T>
        class LuaObject
        {
        public:
            static std::string getClassName()
            {
                return UTIL::rawTypeName<T>();
            }

            static int __new(lua_State * L)
            {
                auto data = (T **)lua_newuserdata(L, sizeof(T *));
                *data = new T();

                /* stack:
                 * USERDATA
                 */

                std::string metatable_name = "LUA_" + UTIL::rawTypeName<T>();
                luaL_getmetatable(L, metatable_name.c_str());

                /* stack:
                 * METATABLE
                 * USERDATA
                 */

                lua_setmetatable(L, -2);

                /* stack:
                 * USERDATA
                 */

                return 1;
            }

            static int __delete(lua_State * L)
            {
                T * t = LuaObject::checkUserData(L, -1);
                delete t;

                return 0;
            }

            static T * checkUserData(lua_State * L, int index)
            {
                std::string metatable_name = "LUA_" + UTIL::rawTypeName<T>();
                return *(T **)luaL_checkudata(L, index, metatable_name.c_str());
            }


        };
    }
}
#endif //TURBO_LUA_DEF_H
