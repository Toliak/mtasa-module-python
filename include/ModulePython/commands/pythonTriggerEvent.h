#pragma once

#include "ModuleSdk/LuaVmExtended.h"

namespace Commands
{

// TODO: comments

void pythonTriggerEventInternal(const std::string &eventName);

int pythonTriggerEvent(lua_State *luaVm);

}