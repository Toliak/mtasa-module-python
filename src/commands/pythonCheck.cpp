#include "ModulePython/commands/pythonCheck.h"
#include "ModulePython/PythonVm.h"

std::string Commands::pythonCheckInternal()
{
    PythonVm *python = PythonVm::getInstance();

    PyObject *moduleString = PyObject_Str(PyModule_GetDict(python->getMainModule()));
    PyObject *moduleStringBytes = PyUnicode_AsEncodedString(moduleString, PythonVm::locale, "strict");

    if (moduleStringBytes != nullptr) {
        return PyBytes_AS_STRING(moduleStringBytes);
    }

    return {};
}

int Commands::pythonCheck(lua_State *luaVm)
{
    LuaVmExtended lua(luaVm);
    lua.pushArgument(pythonCheckInternal());
    return 1;
}
