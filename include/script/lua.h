#ifndef TURBO_LUA_H
#define TURBO_LUA_H

#include <iostream>
#include <sstream>
#include <functional>

#ifdef __cplusplus
    # include <lua.hpp>
#else
    # include <lua.h>
    # include <lualib.h>
    # include <lauxlib.h>
#endif


#include "script/script_def.h"

namespace TURBO
{
    namespace SCRIPT
    {
        class Lua
        {
        private:
            lua_State *lua_state;
        public:
            explicit Lua();
            ~Lua();
            int call(std::string filename);
            int registerFunction(std::string name, lua_CFunction function);
        };
    }
}

#endif //TURBO_LUA_H
