#include "ModulePython/modules/Modules.h"
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

    instance->mainModule = PyImport_AddModule("__main__");
    instance->globalDictionary = PyModule_GetDict(instance->mainModule);

    const wchar_t *pythonPathInit = L"mods/deathmatch/python/__init__.py";
    wchar_t *pyArgv[] = {const_cast<wchar_t *>(pythonPathInit)};
    PySys_SetArgv(
        1,
        pyArgv
    );

    return instance;
}

void PythonVm::initPythonVm()
{
    Py_Initialize();
}

void PythonVm::destroy()
{
    if (!instance) {
        return;
    }
    instance = nullptr;

    Modules::initedModules.clear();
    Modules::userModules.clear();

    Py_Finalize();
}
