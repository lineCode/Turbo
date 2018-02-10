#ifndef TURBO_PYTHON_H
#define TURBO_PYTHON_H

#include <string>
#include <cmath>
#include <fstream>

#include <Python.h>

#include "script/script_def.h"

namespace TURBO
{
    namespace SCRIPT
    {
        class Python
        {
        public:
            Python();
            void callString(std::string content);
            void callScript(std::string filename);
            void registerFunction(std::string name, PyObject * function);
        };
    }
}

#endif //TURBO_PYTHON_H
