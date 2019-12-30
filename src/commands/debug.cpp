#include "ModulePython/commands/debug.h"

void Commands::debugInternal(lua_State *luaVm, const std::list<LuaArgument> &args)
{
    LuaVmExtended lua(luaVm);
    lua.call("iprint", args);
}

std::string Commands::pythonObjectToString(PyObject *object)
{
    PyObject* repr = PyObject_Repr(object);
    PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
    const char *bytes = PyBytes_AS_STRING(str);

    return bytes;
}
