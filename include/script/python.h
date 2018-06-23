#ifndef TURBO_PYTHON_H
#define TURBO_PYTHON_H

#include <string>
#include <cmath>
#include <fstream>

#include "script/python_def.h"
#include "script/py_rect.h"
#include "script/py_turbo.h"

namespace TURBO
{
    namespace SCRIPT
    {
        class Python
        {
        public:
            Python();
            ~Python();
            void callString(std::string content);
            void callScript(std::string filename);
            void registerFunction(std::string name, PyObject * function);
        };
    }
}

#endif //TURBO_PYTHON_H
