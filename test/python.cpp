#include "turbo.h"

namespace TA = TURBO::AUDIO;
namespace TG = TURBO::GUI;
namespace TCH = TURBO::CHART;
namespace TV = TURBO::VIDEO;
namespace TI = TURBO::INPUT;
namespace TU = TURBO::UTIL;
namespace TM = TURBO::MATH;
namespace TN = TURBO::NET;
namespace TS = TURBO::SYSTEM;
namespace TC = TURBO::SCRIPT;

/* Simple Module */

static PyObject *square(PyObject *self, PyObject *args)
{
    int input;
    if (!PyArg_ParseTuple(args, "i", &input)) {
        return nullptr;
    }

    return PyLong_FromLong((long)input * (long)input);
}

static PyMethodDef Turbo_methods[] = {
    {"square", square, METH_VARARGS, "Returns a square of an integer."},
    {nullptr, nullptr, 0, nullptr}
};

static struct PyModuleDef Turbo_definition = {
    PyModuleDef_HEAD_INIT,
    "Turbo",
    "The Python module for TUrbo",
    -1,
    Turbo_methods
};

/* Class Module */

struct Book
{
    PyObject_HEAD
    int id;
};

static PyMemberDef Book_members[] =
                       {
                           {"id", T_INT, offsetof(Book, id), 0, "book id"},
                           {nullptr}
                       };

static void Book_dealloc(Book *self) {
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Book_new(PyTypeObject *type, PyObject *args,
                          PyObject *kwds) {
    Book *self;

    self = (Book *)type->tp_alloc(type, 0);
    if (self != nullptr) {
        self->id = 0;
    }

    return (PyObject *)self;
}

static int Book_init(Book *self, PyObject *args, PyObject *kwds) {
    self->id = 1;
    return 0;
}

static PyObject *Book_inc(Book *self) {
    self->id++;

    return PyLong_FromLong((long)self->id);
}

static PyObject *Book_dec(Book *self) {
    self->id--;

    return PyLong_FromLong((long)self->id);
}

static PyMethodDef Book_methods[] = {
    {"inc", (PyCFunction)Book_inc, METH_NOARGS, "++"},
    {"dec", (PyCFunction)Book_dec, METH_NOARGS, "--"},
    {nullptr}
};

static PyTypeObject BookType = {
    PyVarObject_HEAD_INIT(nullptr, 0) "Turbo.Book",  /* tp_name */
    sizeof(Book),                           /* tp_basicsize */
    0,                                        /* tp_itemsize */
    (destructor)Book_dealloc,               /* tp_dealloc */
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
    "Book objects",                         /* tp_doc */
    nullptr,                                        /* tp_traverse */
    nullptr,                                        /* tp_clear */
    nullptr,                                        /* tp_richcompare */
    0,                                        /* tp_weaklistoffset */
    nullptr,                                        /* tp_iter */
    nullptr,                                        /* tp_iternext */
    Book_methods,                           /* tp_methods */
    Book_members,                           /* tp_members */
    nullptr,                                        /* tp_getset */
    nullptr,                                        /* tp_base */
    nullptr,                                        /* tp_dict */
    nullptr,                                        /* tp_descr_get */
    nullptr,                                        /* tp_descr_set */
    0,                                        /* tp_dictoffset */
    (initproc)Book_init,                    /* tp_init */
    nullptr,                                        /* tp_alloc */
    Book_new,                               /* tp_new */
};

PyMODINIT_FUNC PyInit_Turbo(void) {
    Py_Initialize();
    PyObject *m = PyModule_Create(&Turbo_definition);

    if (PyType_Ready(&BookType) < 0)
        return nullptr;

    Py_INCREF(&BookType);
    PyModule_AddObject(m, "Book", (PyObject *)&BookType);

    return m;
}

/* Python call */

void python(int argc, char ** argv)
{
    wchar_t *program = Py_DecodeLocale(argv[0], nullptr);
    if (program == nullptr) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    PyImport_AppendInittab("Turbo", PyInit_Turbo);
    Py_SetProgramName(program);
    Py_Initialize();

    PyRun_SimpleString("import Turbo \nprint(Turbo.square(2))");
    PyRun_SimpleString("import Turbo \nb = Turbo.Book()\nb.inc()\nprint(b.id)");

    PyMem_RawFree(program);
}