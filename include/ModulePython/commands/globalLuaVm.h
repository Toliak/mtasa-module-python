#pragma once

#include "ModuleSdk/LuaVmExtended.h"

namespace Commands
{

extern lua_State *globalLuaVm;      ///< Global pointer to Lua virtual machine

/**
 * @brief Call to update global Lua VM pointer
 * @param luaVm New pointer
 */
void updateGlobalLuaVm(lua_State *luaVm);

}