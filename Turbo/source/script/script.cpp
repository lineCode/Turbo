#include "script/script.h"

using namespace SCRIPT;

Python::Python()
{
    //TODO???Py_SetPythonHome((wchar_t*)"C:/Libs/Python");
    Py_Initialize();
}

void Python::runCommand(string command)
{
    PyRun_SimpleString(command.c_str());
}

Python::~Python()
{
    Py_Finalize();
}