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

        };

        static PyObject *_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
        {
            Rect *self = (Rect *) type->tp_alloc(type, 0);
            return (PyObject *) self;
        }

        static void _delete(Rect *self)
        {
            Py_TYPE(self)->tp_free((PyObject *) self);
        }

        static int _init(Rect *self, PyObject *args, PyObject *kwds)
        {
            return 0;
        }

        static PyObject *center(Rect *self)
        {
            return PyLong_FromLong((long) 0);
        }

        static PyMemberDef Rect_members[] = {
            {"x", T_INT, offsetof(Rect, x), 0, ""},
            {"y", T_INT, offsetof(Rect, y), 1, ""},
            {"w", T_INT, offsetof(Rect, w), 2, ""},
            {"h", T_INT, offsetof(Rect, h), 3, ""},
            {nullptr}
        };

        static PyMethodDef Rect_methods[] = {
            {"center", (PyCFunction) center, METH_NOARGS, ""},
            {nullptr}
        };

        static PyTypeObject RectType = {
            PyVarObject_HEAD_INIT(nullptr, 0)
            "Turbo.Rect",  /* tp_name */
            sizeof(Rect),                           /* tp_basicsize */
            0,                                        /* tp_itemsize */
            (destructor) _delete,               /* tp_dealloc */
            nullptr,                                        /* tp_print */
            nullptr,                                        /* tp_getattr */
            nullptr,                                        /* tp_setattr */
            nullptr,                                        /* tp_reserved */
            nullptr,                                        /* tp_repr */
            nullptr,                                        /* tp_as_number */
            nullptr,                                        /* tp_as_sequence */
            nullptr,                                        /* tp_as_mapping */
            nullptr,                                        /* tp_hash  */
            nullptr,                                        /* tp_call */
            nullptr,                                        /* tp_str */
            nullptr,                                        /* tp_getattro */
            nullptr,                                        /* tp_setattro */
            nullptr,                                        /* tp_as_buffer */
            Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
            nullptr,                         /* tp_doc */
            nullptr,                                        /* tp_traverse */
            nullptr,                                        /* tp_clear */
            nullptr,                                        /* tp_richcompare */
            0,                                        /* tp_weaklistoffset */
            nullptr,                                        /* tp_iter */
            nullptr,                                        /* tp_iternext */
            Rect_methods,                           /* tp_methods */
            Rect_members,                           /* tp_members */
            nullptr,                                        /* tp_getset */
            nullptr,                                        /* tp_base */
            nullptr,                                        /* tp_dict */
            nullptr,                                        /* tp_descr_get */
            nullptr,                                        /* tp_descr_set */
            0,                                        /* tp_dictoffset */
            (initproc) _init,                    /* tp_init */
            nullptr,                                        /* tp_alloc */
            _new,                               /* tp_new */
        };
    }
}

#endif //TURBO_PY_RECT_H
