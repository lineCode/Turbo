#include "script/lua.h"

namespace TURBO
{
    namespace SCRIPT
    {
        Lua::Lua()
        {
            lua_state = luaL_newstate();
            luaL_openlibs(lua_state);
        }

        Lua::~Lua()
        {
            lua_close(lua_state);
        }

        int Lua::callString(std::string content)
        {
            luaL_dostring (lua_state, content.c_str());
            return 1;
        }

        int Lua::callScript(std::string filename)
        {
            // Remove
            //luaL_requiref(lua_state, "io", luaopen_io, 1);

//            if(luaL_loadfile(lua_state, filename.c_str()) == LUA_OK)
//            {
//                return lua_pcall(lua_state, 0, LUA_MULTRET, 0);
//            }
//            else
//            {
//                return -1;
//            }
            luaL_dofile(lua_state, filename.c_str());
            return 1;
        }

        int Lua::registerFunction(std::string name, lua_CFunction function)
        {
            lua_register(lua_state, name.c_str(), function);
            return 1;
        }
    }
}