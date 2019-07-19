#include "ModulePython/commands/globalLuaVm.h"

lua_State * Commands::globalLuaVm = nullptr;

void Commands::updateGlobalLuaVm(lua_State *luaVm)
{
    Commands::globalLuaVm = luaVm;
}
