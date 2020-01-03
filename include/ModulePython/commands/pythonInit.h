#pragma once

#include "ModuleSdk/LuaVmExtended.h"

namespace Commands
{

/**
 * @brief Python initializer function
 * @param luaVm Lua VM pointer
 * @return Return arguments amount
 */
int pythonInit(lua_State *luaVm);

}