#include "script/lua.h"

namespace TURBO
{
    namespace SCRIPT
    {
        LuaObject::LuaObject(std::string class_name)
            : class_name(class_name)
        {

        }

        std::string LuaObject::getClassName()
        {
            return class_name;
        }

        void LuaObject::registerObject(lua_State *state)
        {

        }

        TestObject::TestObject()
            : LuaObject(__FUNCTION__)
        {

        }

        Lua::Lua()
        {
            lua_state = luaL_newstate();
            luaL_openlibs(lua_state);
        }

        Lua::~Lua()
        {
            lua_close(lua_state);
        }

        lua_State *Lua::getState()
        {
            return lua_state;
        }

        void Lua::pop()
        {
            lua_pop(lua_state, -1);
        }

        std::string Lua::getError()
        {
            return lua_tostring(lua_state, -1);
        }

        void Lua::printError(std::string function)
        {
            if(!function.empty())
            {
                std::cout << "Error in '" << function << "': " << getError() << std::endl;
            }
            else
            {
                std::cout << getError() << std::endl;
            }
        }

        std::string Lua::getString()
        {
            return lua_tostring(lua_state, -1);
        }

        void Lua::getGlobal(std::string name)
        {
            lua_getglobal(lua_state, name.c_str());
        }

        bool Lua::getGlobalFunction(std::string name)
        {
            return false;
        }

        int Lua::callString(std::string content)
        {
            if(luaL_dostring(lua_state, std::regex_replace(content, std::regex("\\s"), "").c_str()))
            {
                printError(__FUNCTION__);
                return 1;
            }
            return 0;
        }

        int Lua::callScript(std::string filename)
        {
            if(UTIL::Dir::isFile(filename))
            {
                if(luaL_dofile(lua_state, filename.c_str()))
                {
                    printError(__FUNCTION__);
                    return 1;
                }
            }
            return 0;
        }

        int Lua::loadScript(std::string filename)
        {
            if(UTIL::Dir::isFile(filename))
            {
                if(luaL_loadfile(lua_state, filename.c_str()))
                {
                    printError(__FUNCTION__);
                    return 1;
                }
                return 0;
            }
            return 1;
        }

        int Lua::registerFunction(std::string name, lua_CFunction function)
        {
            lua_register(lua_state, name.c_str(), function);
            return 0;
        }
    }
}