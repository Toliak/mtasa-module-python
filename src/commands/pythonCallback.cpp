#include "ModulePython/PythonVm.h"
#include "ModulePython/commands/globalLuaVm.h"
#include "ModulePython/commands/pythonCallback.h"

uintptr_t Commands::pythonCallbackInternal()
{
    PythonVm::getInstance();

    PyObject *pName = PyUnicode_FromString("main");
    PyObject *pModule = PyImport_Import(pName);
    PyObject *pDict = PyModule_GetDict(pModule);
    PyObject *callable = PyDict_GetItemString(pDict, "callback_function");

    PyObject *result = PyObject_CallFunction(callable, "()");

    return reinterpret_cast<uintptr_t>(result);
}

int Commands::pythonCallback(lua_State *luaVm)
{
    updateGlobalLuaVm(luaVm);
    LuaVmExtended lua(luaVm);

    int a = pythonCallbackInternal();
    lua.pushArgument(a);
    return 1;
}

