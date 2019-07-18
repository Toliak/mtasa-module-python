#pragma once

#include "ModuleSdk/LuaVmExtended.h"

namespace Commands
{

std::string pythonCheckInternal();

int pythonCheck(lua_State *luaVm);

}