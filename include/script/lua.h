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

#include "util/dir.h"

namespace TURBO
{
    namespace SCRIPT
    {
        class LuaObject
        {
        private:
            std::string class_name;

        public:
            explicit LuaObject(std::string class_name);
            std::string getClassName();
        };

        class TestObject : public LuaObject
        {
        public:
            TestObject();
        };

        class Lua
        {
        private:
            lua_State *lua_state;

        public:
            explicit Lua();
            ~Lua();
            lua_State *getState();
            void pop();
            std::string getError();
            void printError(std::string function = "");
            void getGlobal(std::string name);
            bool getGlobalFunction(std::string name);
            std::string getString();
            int callString(std::string content);
            int callScript(std::string filename);
            int loadScript(std::string filename);
            int callFunctionFromScript(std::string filename, std::string function);
            int registerFunction(std::string name, lua_CFunction function);
        };
    }
}

#endif //TURBO_LUA_H
