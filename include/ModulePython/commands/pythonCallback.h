#pragma once

#include "ModuleSdk/LuaVmExtended.h"

namespace Commands
{

// TODO: remove

uintptr_t pythonCallbackInternal();

int pythonCallback(lua_State *luaVm);

}