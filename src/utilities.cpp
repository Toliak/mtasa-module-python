#include "ModulePython/utilities.h"

namespace Utilities
{

void iprint(lua_State *luaVm, const std::list<LuaArgument> &args)
{
    LuaVmExtended lua(luaVm);

    lua.call("iprint", args);
}

void error(lua_State *luaVm, const std::string &errorMessage)
{
    LuaVmExtended lua(luaVm);

    lua.call("outputDebugString", {errorMessage, 1});
}

std::string pythonObjectToString(PyObject *object)
{
    PyObject *repr = PyObject_Repr(object);
    PyObject *str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
    const char *bytes = PyBytes_AS_STRING(str);

    return bytes;
}

}