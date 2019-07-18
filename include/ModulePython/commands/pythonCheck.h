#pragma once

#include "ModuleSdk/LuaVmExtended.h"

namespace Commands
{

int pythonCheck(lua_State *luaVm)
{
    LuaVmExtended lua(luaVm);
    PythonVm *python = PythonVm::getInstance();

    PyObject *cXepom = PyObject_Str(PyModule_GetDict(python->getMainModule()));
    PyObject *temp_bytes = PyUnicode_AsEncodedString(cXepom, PythonVm::locale, "strict"); // Owned reference
    if (temp_bytes != nullptr) {
        lua.pushArgument(PyBytes_AS_STRING(temp_bytes));
        return 1;
    }

    return 0;
}

std::string pythonCheckInternal()
{

}

}