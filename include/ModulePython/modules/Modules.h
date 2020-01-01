#pragma once

#include <ModulePython/PythonModule.h>
#include <unordered_map>
#include <set>


namespace Modules
{

extern std::set<PythonModule *> initedModules;      ///< Global set of initialized core modules
extern std::unordered_map<std::string, PyObject *> userModules;      ///< Global map of initialized user modules

}