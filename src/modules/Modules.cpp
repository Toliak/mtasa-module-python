#include "ModulePython/modules/Modules.h"

namespace Modules
{

std::set<PythonModule *> initedModules{};
std::unordered_map<std::string, PyObject *> userModules{};

}