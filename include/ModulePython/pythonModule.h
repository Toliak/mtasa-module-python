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

static PyMethodDef mtasaCoreMethods[] = {
    {"test", spam_system, METH_VARARGS, "Execute a shell command."},
    {NULL, NULL, 0, NULL}        // Sentinel
};

//static PyMod

static struct PyModuleDef mtasaCoreModule = {
    PyModuleDef_HEAD_INIT,
    "_mtasa_core",   /* name of module */
    nullptr, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    mtasaCoreMethods
};

static PyMethodDef mtasaMethods[] = {
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
PyInit_mtasaCore(void)
{
    PyObject *m;

    m = PyModule_Create(&mtasaCoreModule);

    return m;
}

PyMODINIT_FUNC
PyInit_mtasa(void)
{
    PyObject *m;

    m = PyModule_Create(&mtasaModule);
    if (m == NULL)
        return NULL;

    SpamError = PyErr_NewException("mtasa.error", NULL, NULL);
    Py_INCREF(SpamError);
    PyModule_AddObject(m, "error", SpamError);

    PyObject *ownDict = PyModule_GetDict(m);
    PyDict_SetItem(
        ownDict,
        PyUnicode_FromString("core"),
        PyInit_mtasaCore()
    );

    PyObject *localDictionary = PyDict_New();
    PyObject *globalDictionary = PyModule_GetDict(m);
//
//    PyRun_String("mtasa.__package__ = mtasa", Py_file_input, globalDictionary, localDictionary);
//    PyRun_String("mtasa.core.__package__ = mtasa", Py_file_input, globalDictionary, localDictionary);

    return m;
}