#include "ModulePython/commands/pythonCheck.h"
#include "ModulePython/commands/globalLuaVm.h"
#include "ModulePython/PythonVm.h"
#include <fstream>

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
    updateGlobalLuaVm(luaVm);

    LuaVmExtended lua(luaVm);
    lua.pushArgument(pythonCheckInternal());

    std::ifstream file("mods/deathmatch/python/main.py");
    std::string firstLine;
    std::getline(file, firstLine);

    lua.pushArgument(firstLine);
    return 2;
}
