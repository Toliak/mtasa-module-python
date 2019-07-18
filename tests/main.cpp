#include "ModulePython/PythonVm.h"
#include <iostream>

int main()
{
    auto pyVm = PythonVm::init(L"python/bin/python");

    PyObject* main = PyImport_AddModule("__main__");
    PyObject* globalDictionary = PyModule_GetDict(main);
    PyObject* localDictionary = PyDict_New();

    const char* pythonScript = "result = multiplicand * multiplier\n";
    PyDict_SetItemString(localDictionary, "multiplicand", PyLong_FromLong(2));
    PyDict_SetItemString(localDictionary, "multiplier", PyLong_FromLong(5));
    PyRun_String(pythonScript, Py_file_input, globalDictionary, localDictionary);
    PyRun_File()

    long result = PyLong_AsLong(PyDict_GetItemString(localDictionary, "result"));
    std::cout << result << std::endl;

    PyObject *sql = PyImport_AddModule("django");

    PyObject *cXepom = PyObject_Str(PyModule_GetDict(sql));
    PyObject * temp_bytes = PyUnicode_AsEncodedString(cXepom, "UTF-8", "strict"); // Owned reference
    if (temp_bytes != nullptr) {

        std::string a = PyBytes_AS_STRING(temp_bytes); // Borrowed pointer
        std::cout << a << std::endl;
    }

    std::cout << "Fuck yeah\n";
}