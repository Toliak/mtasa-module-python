#include "ModulePython/commands/isPythonInited.h"
#include "ModulePython/commands/globalLuaVm.h"
#include "ModulePython/PythonVm.h"
#include <fstream>

namespace Commands
{

int isPythonInited(lua_State *luaVm)
{
    updateGlobalLuaVm(luaVm);
    LuaVmExtended lua(luaVm);

    lua.pushArgument(PythonVm::getInstance() != nullptr);
    return 1;
}

}