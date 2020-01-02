#pragma once

#include <Python.h>
#include "ModuleSdk/LuaVmExtended.h"
#include "ModuleSdk/LuaArgument.h"

namespace Utilities
{

/**
 * @brief Calls iprint from MTASA
 * @param luaVm Lua VM
 * @param args List of arguments
 */
void iprint(lua_State *luaVm, const std::list<LuaArgument> &args);

/**
 * @brief Prints an error in MTASA console
 * @param luaVm
 * @param errorMessage
 */
void error(lua_State *luaVm, const std::string &errorMessage);

/**
 * @brief Any python object to std::string
 * @param object PyObject pointer
 * @return std::string
 */
std::string pythonObjectToString(PyObject *object);

/**
 * @brief Transforms LuaArgument to Python object
 * @throws LuaUnexpectedType If passed type cannot be transformed into PyObject *
 * @param argument Argument
 * @return PyObject pointer
 */
PyObject *luaArgumentToPyObject(const LuaArgument &argument);

/**
 * @brief TODO
 * @param object
 * @return
 */
LuaArgument pyObjectToLuaArgument(PyObject *object);

}