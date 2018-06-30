#include "script/py_turbo.h"

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

        PyObject *PyInit_Turbo()
        {
            Py_Initialize();
            PyObject *module = PyModule_Create(&TURBO::SCRIPT::Turbo_definition);

            if(PyType_Ready(&Point_definition) < 0)
                return nullptr;

            Py_INCREF(&TURBO::SCRIPT::Point_definition);

            PyModule_AddObject(module, "Point", (PyObject * ) &Point_definition);

            return module;
        }
    }
}