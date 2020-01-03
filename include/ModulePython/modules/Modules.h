#pragma once

#include <ModulePython/PythonModule.h>
#include <unordered_map>
#include <set>


namespace Modules
{

/**
 * @brief Get Python Class from module
 * @param moduleName Module name
 * @param className Class name
 * @throws PythonModuleNotImported
 * @throws PythonClassNotFound
 * @return PyObject pointer to class
 */
PyObject *getPythonClass(const std::string &moduleName, const std::string &className);

/**
 * @brief Get Python function from module
 * @param functionName Function name
 * @param className Class name
 * @throws PythonModuleNotImported
 * @throws PythonFunctionNotFound
 * @return PyObject pointer to function
 */
PyObject *getPythonFunction(const std::string &moduleName, const std::string &functionName);

extern std::set<PythonModule *> initedModules;      ///< Global set of initialized core modules
extern std::unordered_map<std::string, PyObject *> userModules;      ///< Global map of initialized user modules

}