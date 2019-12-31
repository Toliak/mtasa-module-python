#pragma once

#include <ModulePython/PythonModule.h>
#include <set>


namespace Modules
{

extern std::set<PythonModule *> initedModules;      ///< Global set of initialized modules

}