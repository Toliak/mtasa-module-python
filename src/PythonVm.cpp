#include "ModulePython/PythonVm.h"

const char *PythonVm::locale = "UTF-8";

PythonVm *PythonVm::instance = nullptr;

PythonVm *PythonVm::getInstance()
{
    return PythonVm::instance;
}

void PythonVm::initModules()
{

}

void PythonVm::initPythonVm()
{
    Py_Initialize();
}
