#include "script/python.h"

namespace TURBO
{
    namespace SCRIPT
    {
        Python::Python()
        {

        }

        void Python::call(std::string file)
        {
            std::ifstream ifs(file);
            std::string content( (std::istreambuf_iterator<char>(ifs) ),
                                 (std::istreambuf_iterator<char>()    ) );
            PyRun_SimpleString(content.c_str());
        }

        void Python::registerFunction(const std::string name, PyObject * function)
        {
            static struct PyMethodDef methods[] =
                {
                    {name.c_str(), (PyCFunction)function, METH_VARARGS, "description"},
                    {nullptr, nullptr, 0, nullptr}
                };

            static struct PyModuleDef module =
                {
                    PyModuleDef_HEAD_INIT, "module", "description", -1, methods, nullptr, nullptr, nullptr, nullptr
                };
            PyModule_Create(&module);
        }
    }
}