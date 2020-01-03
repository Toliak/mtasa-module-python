#pragma once

#include "ModuleSdk/LuaVmExtended.h"

namespace Commands
{

/**
 * @brief Calls function from Python VM
 * @param luaVm Lua VM
 * @return Returned arguments amount
 */
int pythonCall(lua_State *luaVm);

}