#include "ModulePython/PythonVm.h"
#include "ModulePython/pythonModule.h"

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

    instance->initModules();
    instance->initPythonVm();

    instance->mainModule = PyImport_AddModule("__main__");
    instance->globalDictionary = PyModule_GetDict(instance->mainModule);

    return instance;
}

void PythonVm::initModules()
{
    PyImport_AppendInittab("_mtasa_core", PyInit_mtasaCore);
//    PyImport_AppendInittab("mtasa", PyInit_mtasa);


}

void PythonVm::initPythonVm()
{
    Py_Initialize();
}
