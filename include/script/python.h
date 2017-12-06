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
            void call(std::string file);
            void registerFunction(std::string name, PyObject * function);
        };
    }
}

#endif //TURBO_PYTHON_H
