#include "ModulePython/commands/globalLuaVm.h"
#include "ModulePython/PythonVm.h"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    std::ifstream file("../python/main.py");
    std::string firstLine;
    std::getline(file, firstLine);

    std::cout << firstLine << std::endl;

    auto python = PythonVm::init();

    const wchar_t *myString = L"../python/main.py";

    wchar_t *pyArgv[] = {const_cast<wchar_t *>(myString)};

    PySys_SetArgv(
        1,
        pyArgv
    );

    PyObject *localDictionary = PyDict_New();

//    Commands::globalLuaVm = (lua_State *)444;

    const char *pythonScript = "result = multiplicand * multiplier\n";
    PyDict_SetItemString(localDictionary, "multiplicand", PyLong_FromLong(2));
    PyDict_SetItemString(localDictionary, "multiplier", PyLong_FromLong(5));

    PyRun_String(pythonScript, Py_file_input, python->getGlobalDictionary(), localDictionary);
//    PyModu

    PyErr_Print();

    // Build the name object
    PyObject *pName = PyUnicode_FromString("main");
    PyObject *pModule = PyImport_Import(pName);
    PyObject *pDict = PyModule_GetDict(pModule);
    PyObject *callable = PyDict_GetItemString(pDict, "callback_function");

    std::cout << "Callable? " << PyCallable_Check(callable) << std::endl;

    PyObject *result = PyObject_CallFunction(callable, "()");
    PyErr_Print();

    PyObject *cXepom = PyObject_Str(localDictionary);
    PyObject *temp_bytes = PyUnicode_AsEncodedString(cXepom, "UTF-8", "strict"); // Owned reference
    if (temp_bytes != nullptr) {
        auto t = PyBytes_AS_STRING(temp_bytes);
        std::cout << t << std::endl;
    }


    std::cout << "Fuck yeah\n";
}