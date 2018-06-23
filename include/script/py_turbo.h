#ifndef TURBO_PY_TURBO_H
#define TURBO_PY_TURBO_H

#include "script/python_def.h"

namespace TURBO
{
    namespace SCRIPT
    {
        static PyMethodDef Turbo_methods[] = {
            {nullptr, nullptr, 0, nullptr}
        };

        static struct PyModuleDef Turbo_definition = {
            PyModuleDef_HEAD_INIT,
            "Turbo",
            "The Python module for Turbo",
            -1,
            Turbo_methods
        };
    }
}

#endif //TURBO_PY_TURBO_H
