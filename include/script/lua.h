#ifndef TURBO_LUA_H
#define TURBO_LUA_H

#include <iostream>
#include <sstream>
#include <functional>

#include "script/lua_def.h"
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
            static void registerObject(lua_State *state);
        };

        class TestObject
            : public LuaObject
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

            Lua(lua_State * state);

            ~Lua();

            lua_State *getState();

            void checkStack(int size);

            std::string getError();

            void printError(std::string function = "");

            int callString(std::string content);

            int callScript(std::string filename);

            int loadScript(std::string filename);

            int registerFunction(std::string name, lua_CFunction function);

            bool isFunction(int index = -1);

            void pushCFunction(lua_CFunction func);

            bool isCFunction(int index = -1);

            void pop();

            void push(int index = -1);

            int getType(int index = -1);

            std::string getTypeName(int type);

            int getTop();

            void setTop(int index = -1);

            void remove(int index = -1);

            void insert(int index = -1);

            void replace(int index = -1);

            void getGlobal(std::string name);

            bool getGlobalFunction(std::string name);

            void pushNil();

            bool isNil(int index = -1);

            bool isNone(int index = -1);

            bool isNoneOrNil(int index = -1);

            void pushBool(bool val);

            bool isBool(int index = -1);

            bool getBool(int index = -1);

            void pushNumber(double val);

            bool isNumber(int index = -1);

            double getNumber(int index = -1);

            double checkNumber(int arg);

            void pushString(std::string val);

            bool isString(int index = -1);

            std::string getString(int index = -1);

            std::string checkString(int arg);

            void newTable();

            void newUserTable(int size);

            lua_State *newThread();

            bool isThread(int index = -1);

            template<typename T>
            void registerObject(lua_State *state)
            {
                T::registerObject(state);
            };
        };
    }
}

#endif //TURBO_LUA_H
