#ifndef TURBO_PY_POINT_H
#define TURBO_PY_POINT_H

#include "script/python_def.h"

#include "util/log.h"

namespace TURBO
{
    namespace SCRIPT
    {
        struct Point : public PyClass<Point>
        {
            PyObject_HEAD
            int x = 0;
            int y = 0;
            int z = 0;
        };

        namespace PyPoint
        {
            static int __init__(SCRIPT::Point *self, PyObject *args, PyObject *kwds)
            {
                static char *kwlist[] = {(char *)"x", (char *)"y", (char *)"z", nullptr};
                int x = 0;
                int y = 0;
                int z = 0;

                if(kwlist == nullptr)
                {
                    std::cout << "empty" << "\n";
                }

                if(!PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist, &x, &y, &z))
                {
                    std::string fnc = __FUNCTION__;
                    UTIL::Log::err("Error while parsing " + fnc);
                }
                self->x = x;
                self->y = y;
                self->z = z;
                return 0;
            }

            static PyObject* getX(SCRIPT::Point *self)
            {
                return PyLong_FromLong((long)self->x);
            }

            static PyMemberDef members[] = {
                {(char *)"x", T_INT, offsetof(Point, x), 0, (char *)""},
                {(char *)"y", T_INT, offsetof(Point, y), 0, (char *)""},
                {(char *)"z", T_INT, offsetof(Point, z), 0, (char *)""},
                {nullptr}
            };

            static PyMethodDef methods[] = {
                {"getX", (PyCFunction)getX, METH_NOARGS, ""},
                {nullptr}
            };
        }

        static PyTypeObject Point_definition = {
            PyVarObject_HEAD_INIT(nullptr, 0)
            "Turbo.Point",
            sizeof(Point),
            0,
            (destructor) Point::__delete__,
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
            PyPoint::methods,
            PyPoint::members,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            0,
            (initproc) PyPoint::__init__,
            nullptr,
            Point::__new__,
        };
    }
}

#endif //TURBO_PY_POINT_H
