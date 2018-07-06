#ifndef TURBO_PYTHON_H
#define TURBO_PYTHON_H

#include <string>
#include <cmath>
#include <fstream>

#include "script/python_def.h"
#include "script/py_turbo.h"

#include "util/type.h"

namespace TURBO
{
    namespace SCRIPT
    {
        PyMODINIT_FUNC PyInit_Turbo(void);
    }
}


#endif //TURBO_PYTHON_H
