#include "ModulePython/utilities.h"
#include "ModulePython/commands/globalLuaVm.h"
#include "ModulePython/commands/pythonDestroy.h"
#include "ModulePython/PythonVm.h"

int Commands::pythonDestroy(lua_State *luaVm)
{
    PythonVm::destroy();

    return 0;
}
