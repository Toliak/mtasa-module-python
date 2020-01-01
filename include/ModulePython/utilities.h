#pragma once

#include <Python.h>
#include "ModuleSdk/LuaVmExtended.h"
#include "ModuleSdk/LuaArgument.h"

namespace Utilities
{

void iprint(lua_State *luaVm, const std::list<LuaArgument> &args);

void error(lua_State *luaVm, const std::string &errorMessage);

std::string pythonObjectToString(PyObject *object);

}