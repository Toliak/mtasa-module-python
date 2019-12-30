#include "ModulePython/commands/debug.h"
#include "ModulePython/commands/globalLuaVm.h"
#include "ModulePython/commands/pythonTriggerEvent.h"
#include "ModulePython/PythonVm.h"

void Commands::pythonTriggerEventInternal(const std::string &eventName)
{
    debugInternal(
        globalLuaVm,
        {"entered the internal"}
    );

    PyObject *pName = PyUnicode_FromString("mtasa.event");
    PyObject *pModule = PyImport_Import(pName);

    debugInternal(globalLuaVm, {"pModule", std::to_string((ptrdiff_t) pModule)});

    PyObject *pDict = PyModule_GetDict(pModule);

    PyObject *callable = PyDict_GetItemString(pDict, "trigger_event");

    debugInternal(globalLuaVm, {"callable", std::to_string((ptrdiff_t) callable)});

    PyObject *result = PyObject_CallFunction(callable, "(s)", PyUnicode_FromString(eventName.c_str()));

    debugInternal(
        globalLuaVm,
        {
            std::to_string((ptrdiff_t) result),
        }
    );
}

int Commands::pythonTriggerEvent(lua_State *luaVm)
{
    updateGlobalLuaVm(luaVm);
    LuaVmExtended lua(luaVm);

    std::string eventName;
    try {
        eventName = lua.parseArgument(1, LuaTypeString).toString();
    } catch (LuaException &e) {
        lua.pushArgument({e.what()});
        return 1;
    }
    debugInternal(luaVm, {eventName});

    pythonTriggerEventInternal(eventName);
    return 0;
}
