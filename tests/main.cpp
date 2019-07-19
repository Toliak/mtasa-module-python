#include "ModulePython/PythonVm.h"
#include <iostream>

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    auto python = PythonVm::init();

    const wchar_t *myString = L"/home/toliak/CLionProjects/MtasaModulePython/python-scripts/main.py";

    wchar_t *pyArgv[] = {const_cast<wchar_t *>(myString)};

    PySys_SetArgv(
        1,
        pyArgv
    );

    PyObject *localDictionary = PyDict_New();

    const char *pythonScript = "result = multiplicand * multiplier\n";
    PyDict_SetItemString(localDictionary, "multiplicand", PyLong_FromLong(2));
    PyDict_SetItemString(localDictionary, "multiplier", PyLong_FromLong(5));

    PyRun_String(pythonScript, Py_file_input, python->getGlobalDictionary(), localDictionary);

    PyRun_File(
        fopen("../python-scripts/main.py", "r"),
        "main.py",
        Py_file_input,
        python->getGlobalDictionary(),
        localDictionary
    );
//    PyModu
    PyRun_String("mtasa.test(5)", Py_file_input, python->getGlobalDictionary(), localDictionary);


    long result = PyLong_AsLong(PyDict_GetItemString(localDictionary, "result"));
    std::cout << result << std::endl;

    PyObject *cXepom = PyObject_Str(localDictionary);
    PyObject *temp_bytes = PyUnicode_AsEncodedString(cXepom, "UTF-8", "strict"); // Owned reference
    if (temp_bytes != nullptr) {
        auto t = PyBytes_AS_STRING(temp_bytes);
        std::cout << t << std::endl;
    }

    std::cout << "Fuck yeah\n";
}