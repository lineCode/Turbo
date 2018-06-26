#include "script/python.h"

namespace TURBO
{
    namespace SCRIPT
    {
        void Python::runString(std::string content)
        {
            PyRun_SimpleString(content.c_str());
        }

        void Python::runScript(std::string filename)
        {
            std::ifstream ifs(filename);
            std::string content((std::istreambuf_iterator<char>(ifs)),
                                (std::istreambuf_iterator<char>()   ));
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
                    PyModuleDef_HEAD_INIT,
                    "module",
                    "description",
                    -1,
                    methods,
                    nullptr,
                    nullptr,
                    nullptr,
                    nullptr
                };
            PyModule_Create(&module);
        }

        PyMODINIT_FUNC PyInit_Turbo(void)
        {
            Py_Initialize();
            PyObject *module = PyModule_Create(&TURBO::SCRIPT::Turbo_definition);

            if(PyType_Ready(&PointType) < 0)
                return nullptr;

            Py_INCREF(&TURBO::SCRIPT::PointType);

            PyModule_AddObject(module, "Point", (PyObject * ) &PointType);

            return module;
        }

        void Python::initialize(int init_signals)
        {
            if(init_signals != -1)
            {
                Py_Initialize();
            }
            else
            {
                Py_InitializeEx(init_signals);
            }
        }

        void Python::finalize()
        {
            Py_Finalize();
        }

        bool Python::isInitialized()
        {
            return (Py_IsInitialized() > 0);
        }

        void Python::setProgramName(std::string name)
        {
            wchar_t *program = Py_DecodeLocale(name.c_str(), nullptr);
            Py_SetProgramName(program);
        }

        std::wstring Python::getProgramName()
        {
            //return std::to_wstring(Py_GetProgramName());
            return std::to_wstring(0);
        }

        void Python::freeProgram(std::string name)
        {
            wchar_t *program = Py_DecodeLocale(name.c_str(), nullptr);
            PyMem_RawFree(program);
        }

        void Python::setPath(wchar_t * path)
        {
            Py_SetPath(path);
        }

        std::wstring Python::getPath()
        {
            //return std::to_wstring(Py_GetPath());
            return std::to_wstring(0);
        }

        std::wstring Python::getVersion()
        {
            //return std::to_wstring(Py_GetVersion());
            return std::to_wstring(0);
        }

        bool Python::addModule(std::string name, PyObject* (*f)())
        {
            if(!Python::isInitialized())
            {
                if(PyImport_AppendInittab(name.c_str(), f) >= 0)
                {
                    return true;
                }
                else
                {
                    // Module could not be initialized
                }
            }
            else
            {
                // Python already initialized before module
            }
            return false;
        }

        PyObject *Python::importModule(PyObject *name)
        {
            return PyImport_Import(name);
        }

        PyObject *Python::toUnicode(std::string value)
        {
            return PyUnicode_FromString(value.c_str());
        }

        PyObject *Python::toFloat(double value)
        {
            return PyFloat_FromDouble(value);
        }

        PyObject *Python::toLong(size_t value)
        {
            return PyLong_FromSize_t(value);
        }

        long Python::asLong(PyObject *value)
        {
            return PyLong_AsLong(value);
        }

        size_t Python::asInt(PyObject *value)
        {
            return PyLong_AsSize_t(value);
        }
    }
}