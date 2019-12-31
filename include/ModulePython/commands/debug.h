#pragma once

#include <Python.h>
#include "ModuleSdk/LuaVmExtended.h"
#include "ModuleSdk/LuaArgument.h"

namespace Commands
{

// TODO: move into nested namespace

void debugInternal(lua_State *luaVm, const std::list<LuaArgument> &args);

std::string pythonObjectToString(PyObject *object);

}