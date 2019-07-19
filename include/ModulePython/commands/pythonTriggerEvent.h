#pragma once

#include "ModuleSdk/LuaVmExtended.h"

namespace Commands
{

void pythonTriggerEventInternal(const std::string &eventName);

int pythonTriggerEvent(lua_State *luaVm);

}