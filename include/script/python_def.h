#ifndef TURBO_PYTHON_DEF_H
#define TURBO_PYTHON_DEF_H

#include "script_def.h"

#include <Python.h>
#include <structmember.h>

namespace TURBO
{
    namespace SCRIPT
    {
        template<typename T>
        class PyClass
        {
        public:
            PyClass(){};
            static PyObject * __new__(PyTypeObject *type, PyObject *args, PyObject *kwds)
            {
                T *self = (T *) type->tp_alloc(type, 0);
                return (PyObject *) self;
            }

            static void __delete__(T *self)
            {
                Py_TYPE(self)->tp_free((PyObject *) self);
            }
        };
    }
}

#endif //TURBO_PYTHON_DEF_H
