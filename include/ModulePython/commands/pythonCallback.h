#pragma once

#include "ModuleSdk/LuaVmExtended.h"

namespace Commands
{

uintptr_t pythonCallbackInternal();

int pythonCallback(lua_State *luaVm);

}