#include "ModulePython/PythonVm.h"

const char *PythonVm::locale = "UTF-8";

PythonVm *PythonVm::instance = nullptr;

PythonVm *PythonVm::init(const std::wstring &programName,
                         const std::wstring &pythonPath,
                         const std::wstring &pythonHome)
{
    if (instance) {
        return instance;
    }

    instance = new PythonVm();
    if (!programName.empty()) {
        Py_SetProgramName(programName.c_str());
    }
    if (!pythonPath.empty()) {
        Py_SetPath(pythonPath.c_str());
    }
    if (!pythonHome.empty()) {
        Py_SetPythonHome(pythonHome.c_str());
    }

    instance->initPythonVm();
    instance->initModules();
    return instance;
}

void PythonVm::initModules()
{
    this->mainModule = PyImport_AddModule("__main__");

    this->globalDictionary = PyModule_GetDict(mainModule);
}

void PythonVm::initPythonVm()
{
    Py_Initialize();
}
