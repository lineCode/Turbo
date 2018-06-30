#include <util/file.h>
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
            PyRun_SimpleString(UTIL::File::getFileContents(filename).c_str());
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

        bool Python::addModule(const char *name, PyObject* (*f)())
        {
            if(!Python::isInitialized())
            {
                if(PyImport_AppendInittab(name, f) >= 0)
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

        PyObject *Python::callObject(PyObject *func, PyObject *args)
        {
            return PyObject_CallObject(func, args);
        }

        PyObject *Python::getAttritbuteFromString(PyObject *obj, std::string attr)
        {
            return PyObject_GetAttrString(obj, attr.c_str());
        }

        bool Python::setAttritbuteFromString(PyObject *obj, std::string attr, PyObject *val)
        {
            return PyObject_SetAttrString(obj, attr.c_str(), val);
        }

        PyObject *Python::getAttritbuteFromObject(PyObject *obj, PyObject *attr)
        {
            return PyObject_GetAttr(obj, attr);
        }

        bool Python::setAttritbuteFromObject(PyObject *obj, PyObject *attr, PyObject *val)
        {
            return PyObject_SetAttr(obj, attr, val);
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