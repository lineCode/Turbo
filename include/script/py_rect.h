#ifndef TURBO_PY_RECT_H
#define TURBO_PY_RECT_H

#include "math/rect.h"

#include "script/python_def.h"

namespace TURBO
{
    namespace SCRIPT
    {
        struct Rect
            : public MATH::Rect
        {
            PyObject_HEAD
        };

        static PyObject * Rect_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
        {
            Rect *self = (Rect *) type->tp_alloc(type, 0);
            return (PyObject *) self;
        }

        static void Rect_delete(Rect *self)
        {
            Py_TYPE(self)->tp_free((PyObject *) self);
        }

        static int Rect__init__(Rect *self, PyObject *args, PyObject *kwds)
        {
            self->x = 0;
            self->y = 0;
            self->w = 0;
            self->h = 0;
            return 0;
        }

        static PyObject * center(Rect *self)
        {
            return PyLong_FromLong((long) 0);
        }

        static PyMemberDef Rect_members[] = {
            {"x", T_INT, offsetof(Rect, x), 0, ""},
            {"y", T_INT, offsetof(Rect, y), 0, ""},
            {"w", T_INT, offsetof(Rect, w), 0, ""},
            {"h", T_INT, offsetof(Rect, h), 0, ""},
            {nullptr}
        };

        static PyMethodDef Rect_methods[] = {
            {"center", (PyCFunction) center, METH_NOARGS, ""},
            {nullptr}
        };

        static PyTypeObject RectType = {
            PyVarObject_HEAD_INIT(nullptr, 0)
            "Turbo.Rect",
            sizeof(Rect),
            0,
            (destructor) Rect_delete,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            0,
            nullptr,
            nullptr,
            Rect_methods,
            Rect_members,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            0,
            (initproc) Rect__init__,
            nullptr,
            Rect_new,
        };
    }
}

#endif //TURBO_PY_RECT_H
