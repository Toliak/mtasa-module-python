#include "ModulePython/Exception.h"
#include "ModulePython/modules/Modules.h"

namespace Modules
{

PyObject *getPythonClass(const std::string &moduleName, const std::string &className)
{
    PyObject *module;
    try {
        module = Modules::userModules.at(moduleName);
    } catch (std::out_of_range &exception) {
        throw PythonModuleNotImported{moduleName};
    }

    PyObject *dict = PyModule_GetDict(module);
    PyObject *elementClass = PyDict_GetItemString(dict, className.c_str());
    if (!elementClass) {
        throw PythonClassNotFound{className, moduleName};
    }

    return elementClass;
}

PyObject *getPythonFunction(const std::string &functionName, const std::string &className)
{
    PyObject *module;
    try {
        module = Modules::userModules.at(functionName);
    } catch (std::out_of_range &exception) {
        throw PythonModuleNotImported{functionName};
    }

    PyObject *dict = PyModule_GetDict(module);
    PyObject *function = PyDict_GetItemString(dict, className.c_str());
    if (!function) {
        throw PythonFunctionNotFound{className, functionName};
    }

    return function;
}

std::set<PythonModule *> initedModules{};
std::unordered_map<std::string, PyObject *> userModules{};

}