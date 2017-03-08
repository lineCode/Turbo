#include "script/Turbo_script.h"

using namespace SCRIPT;

Python::Python()
{
    Py_SetPythonHome((wchar_t*)"C:/Libs/Python");
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
        "print('Today is', ctime(time()))\n");
    Py_Finalize();
}

Python::~Python()
{

}