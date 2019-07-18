#include "ModulePython/PythonVm.h"
#include <iostream>

int main()
{
    auto python = PythonVm::init();

    PyObject *localDictionary = PyDict_New();

    const char *pythonScript = "result = multiplicand * multiplier\n";
    PyDict_SetItemString(localDictionary, "multiplicand", PyLong_FromLong(2));
    PyDict_SetItemString(localDictionary, "multiplier", PyLong_FromLong(5));
    PyRun_String(pythonScript, Py_file_input, python->getGlobalDictionary(), localDictionary);

    long result = PyLong_AsLong(PyDict_GetItemString(localDictionary, "result"));
    std::cout << result << std::endl;

    PyObject *cXepom = PyObject_Str(PyModule_GetDict(python->getMainModule()));
    PyObject *temp_bytes = PyUnicode_AsEncodedString(cXepom, "UTF-8", "strict"); // Owned reference
    if (temp_bytes != nullptr) {
        auto t = PyBytes_AS_STRING(temp_bytes);
        std::cout << t << std::endl;
    }

    std::cout << "Fuck yeah\n";
}