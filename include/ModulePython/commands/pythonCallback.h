#pragma once

#include "ModuleSdk/LuaVmExtended.h"

namespace Commands
{

long pythonCallbackInternal();

int pythonCallback(lua_State *luaVm);

}