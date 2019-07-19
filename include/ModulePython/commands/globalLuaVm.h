#pragma once

#include "ModuleSdk/LuaVmExtended.h"

namespace Commands
{

extern lua_State *globalLuaVm;

void updateGlobalLuaVm(lua_State *luaVm);

}