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

        Lua::Lua(lua_State * state)
            : lua_state(state)
        {

        }

        Lua::~Lua()
        {
            lua_close(lua_state);
        }

        lua_State *Lua::getState()
        {
            return lua_state;
        }

        void Lua::checkStack(int size)
        {
            lua_checkstack(lua_state, size);
        }

        std::string Lua::getError()
        {
            return lua_tostring(lua_state, -1);
        }

        void Lua::printError(std::string function)
        {
            if(!function.empty())
            {
                std::cout << "Error in '" << function << "': " << getError() << "\n";
            }
            else
            {
                std::cout << getError() << "\n";
            }
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

        bool Lua::isFunction(int index)
        {
            return lua_isfunction(lua_state, index) > 0;
        }

        void Lua::pushCFunction(lua_CFunction func)
        {
            lua_pushcfunction(lua_state, func);
        }

        bool Lua::isCFunction(int index)
        {
            return lua_iscfunction(lua_state, index) > 0;
        };

        void Lua::pop()
        {
            lua_pop(lua_state, -1);
        }

        void Lua::push(int index)
        {
            lua_pushvalue(lua_state, index);
        }

        int Lua::getType(int index)
        {
            return lua_type(lua_state, index);
        }

        std::string Lua::getTypeName(int type)
        {
            return lua_typename(lua_state, type);
        }

        int Lua::getTop()
        {
            return lua_gettop(lua_state);
        }

        void Lua::setTop(int index)
        {
            lua_settop(lua_state, index);
        }

        void Lua::remove(int index)
        {
            lua_remove(lua_state, index);
        }

        void Lua::insert(int index)
        {
            lua_insert(lua_state, index);
        }

        void Lua::replace(int index)
        {
            lua_replace(lua_state, index);
        }

        void Lua::getGlobal(std::string name)
        {
            lua_getglobal(lua_state, name.c_str());
        }

        bool Lua::getGlobalFunction(std::string name)
        {
            return false;
        }

        void Lua::pushNil()
        {
            lua_pushnil(lua_state);
        }

        bool Lua::isNil(int index)
        {
            return lua_isnil(lua_state, index) > 0;
        }

        bool Lua::isNone(int index)
        {
            return lua_isnone(lua_state, index) > 0;
        }

        bool Lua::isNoneOrNil(int index)
        {
            return lua_isnoneornil(lua_state, index) > 0;
        }

        void Lua::pushBool(bool val)
        {
            lua_pushboolean(lua_state, val);
        }

        bool Lua::isBool(int index)
        {
            return lua_isboolean(lua_state, index) > 0;
        }

        bool Lua::getBool(int index)
        {
            return lua_toboolean(lua_state, index) > 0;
        }

        void Lua::pushNumber(double val)
        {
            lua_pushnumber(lua_state, val);
        }

        bool Lua::isNumber(int index)
        {
            return lua_isnumber(lua_state, index) > 0;
        }

        double Lua::getNumber(int index)
        {
            return lua_tonumber(lua_state, index);
        }

        double Lua::checkNumber(int arg)
        {
            return luaL_checknumber(lua_state, arg);
        }

        void Lua::pushString(std::string val)
        {
            lua_pushstring(lua_state, val.c_str());
        }

        bool Lua::isString(int index)
        {
            return lua_isstring(lua_state, index) > 0;
        }

        std::string Lua::checkString(int arg)
        {
            return luaL_checkstring(lua_state, arg);
        }

        std::string Lua::getString(int index)
        {
            return lua_tostring(lua_state, -1);
        }

        void Lua::newTable()
        {
            lua_newtable(lua_state);
        }

        int Lua::newMetaTable(std::string name)
        {
            return luaL_newmetatable(lua_state, name.c_str());
        }

        void Lua::getMetaTable(std::string name)
        {
            luaL_getmetatable(lua_state, name.c_str());
        }

        void *Lua::newUserData(size_t size)
        {
            return lua_newuserdata(lua_state, size);
        }

        void *Lua::checkUserData(std::string name, int index)
        {
            return luaL_checkudata(lua_state, index, name.c_str());
        }

        void Lua::pushLightUserData(void *data)
        {
            lua_pushlightuserdata(lua_state, data);
        }

        lua_State * Lua::newThread()
        {
            return lua_newthread(lua_state);
        }

        bool Lua::isThread(int index)
        {
            return lua_isthread(lua_state, index) > 0;
        }
    }
}