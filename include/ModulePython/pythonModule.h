#pragma once

#include <Python.h>

static PyObject *
spam_system(PyObject *self, PyObject *args)
{
    Py_ssize_t pointer;

    if (!PyArg_ParseTuple(args, "n", &pointer)) {
        PyErr_SetString(PyExc_TypeError, "Parameter must be integer");
        return nullptr;
    }

    return PyLong_FromLong(pointer * 2);
}

static PyMethodDef mtasaMethods[] = {
    {"test", spam_system, METH_VARARGS, "Execute a shell command."},
    {NULL, NULL, 0, NULL}        // Sentinel
};

static struct PyModuleDef mtasaModule = {
    PyModuleDef_HEAD_INIT,
    "mtasa",   /* name of module */
    nullptr, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    mtasaMethods
};

static PyObject *SpamError;

PyMODINIT_FUNC
PyInit_spam(void)
{
    PyObject *m;

    m = PyModule_Create(&mtasaModule);
    if (m == NULL)
        return NULL;

    SpamError = PyErr_NewException("mtasa.error", NULL, NULL);
    Py_INCREF(SpamError);
    PyModule_AddObject(m, "error", SpamError);
    return m;
}