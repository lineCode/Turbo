#ifndef TURBO_PYTHON_DEF_H
#define TURBO_PYTHON_DEF_H

#include <Python.h>
#include <structmember.h>

#include "script_def.h"
#include "util/type.h"
#include "util/log.h"

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

        class Python
        {
        public:
            static void runString(std::string content);

            static void runScript(std::string filename);

            static void initialize(int init_signals = -1);

            static void finalize();

            static bool isInitialized();

            static void setProgramName(std::string name);

            static std::wstring getProgramName();

            static void freeProgram(std::string name);

            static void setPath(wchar_t * path);

            static std::wstring getPath();

            static std::wstring getVersion();

            static bool addModule(const char *name, PyObject* (*f)());

            static PyObject *importModule(PyObject *name);

            static PyObject *callObject(PyObject * f, PyObject *args);

            static PyObject *getAttritbuteFromString(PyObject *o, std::string attr);

            static bool setAttritbuteFromString(PyObject *o, std::string attr, PyObject *val);

            static PyObject *getAttritbuteFromObject(PyObject *o, PyObject *attr);

            static bool setAttritbuteFromObject(PyObject *o, PyObject *attr, PyObject * val);

            static PyObject *toUnicode(std::string value);

            static PyObject *toFloat(double value);

            static PyObject *toLong(size_t value);

            static std::string asUnicode(PyObject *value)
            {
                char * msg = PyUnicode_AsUTF8(value);
                std::cout <<  msg << std::endl;
                return "";
            }

            template<typename T = float>
            static double asDouble(PyObject *value)
            {
                auto type = UTIL::rawTypeName<T>();

                if(type == "long")
                {
                    return PyLong_AsDouble(value);
                }
                else if(type == "float")
                {
                    return PyFloat_AsDouble(value);
                }
            }

            static long asLong(PyObject *value);

            static size_t asInt(PyObject *value);

            template<typename ... T>
            static PyObject *toTuple(unsigned argc, T ... argv)
            {
                return PyTuple_Pack(argc, argv...);
            }

            template<typename ... T>
            static PyObject *buildValue(std::string pattern, T ... argv)
            {
                return Py_BuildValue(pattern.c_str(), argv...);
            }
        };
    }
}

#endif //TURBO_PYTHON_DEF_H
