#ifndef TURBO_PYTHON_H
#define TURBO_PYTHON_H

#include <string>
#include <cmath>
#include <fstream>

#include "script/python_def.h"
#include "script/py_point.h"
#include "script/py_rect.h"
#include "script/py_turbo.h"

#include "util/type.h"

namespace TURBO
{
    namespace SCRIPT
    {
        class Python
        {
        public:
            static void runString(std::string content);

            static void runScript(std::string filename);

            static void registerFunction(std::string name, PyObject *function);

            static void initialize(int init_signals = -1);

            static void finalize();

            static bool isInitialized();

            static void setProgramName(std::string name);

            static std::wstring getProgramName();

            static void freeProgram(std::string name);

            static void setPath(wchar_t * path);

            static std::wstring getPath();

            static std::wstring getVersion();

            static bool addModule(std::string name, PyObject* (*f)());

            static PyObject *importModule(PyObject *name);

            static PyObject *toUnicode(std::string value);

            static PyObject *toFloat(double value);

            static PyObject *toLong(size_t value);

            template<typename T>
            static double asDouble(PyObject *value)
            {
                auto type = UTIL::typeName<T>();
                if(type == "float")
                {
                    return PyFloat_AsDouble(value);
                }
                else if(type == "long")
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

        PyMODINIT_FUNC PyInit_Turbo(void);
    }
}


#endif //TURBO_PYTHON_H
