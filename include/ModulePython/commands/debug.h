#pragma once

#include "ModuleSdk/LuaVmExtended.h"
#include "ModuleSdk/LuaArgument.h"

namespace Commands
{

void debugInternal(lua_State *luaVm, const std::list<LuaArgument> &args)
{
    LuaVmExtended lua(luaVm);
    lua.call("iprint", args);
}

}