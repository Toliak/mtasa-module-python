#pragma once

#include "ModuleSdk/LuaVmExtended.h"

namespace Commands
{

/**
 * @brief Checks is Python VM already created
 * @param luaVm Lua VM
 * @return Returned arguments amount
 */
int isPythonInited(lua_State *luaVm);

}