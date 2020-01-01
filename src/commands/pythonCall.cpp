#include "ModulePython/modules/Modules.h"
#include "ModulePython/Exception.h"
#include "ModulePython/utilities.h"
#include "ModulePython/PythonVm.h"
#include "ModulePython/commands/globalLuaVm.h"
#include "ModulePython/commands/pythonCall.h"


using ArgumentList = std::list<LuaArgument>;

// TODO: provide passing userdata

int pythonCallInternal(const std::string &moduleName,
                        const std::string &functionName,
                        const ArgumentList &arguments)
{
    PythonVm::getInstance();

    auto moduleIterator = Modules::userModules.find(moduleName);
    if (moduleIterator == Modules::userModules.cend()) {
        throw PythonModuleNotImported{moduleName};
    }
    PyObject *module = moduleIterator->second;

    Utilities::iprint(Commands::globalLuaVm,
                      {"Argument size", (int) arguments.size()});
    Utilities::iprint(Commands::globalLuaVm,
                      {"module ptr", std::to_string((uintptr_t) module)});

    PyObject *dict = PyModule_GetDict(module);
    PyObject *callable = PyDict_GetItemString(dict, functionName.c_str());

    PyObject *resultTuple = PyObject_CallFunction(callable, "()");

    PyTypeObject* type = resultTuple->ob_type;
    const char* cTypeName = type->tp_name;
    Utilities::iprint(Commands::globalLuaVm,
                      {"typename", cTypeName});

    int result = PyLong_AsLong(resultTuple);

    return result;
}

int Commands::pythonCall(lua_State *luaVm)
{
    updateGlobalLuaVm(luaVm);
    LuaVmExtended lua(luaVm);

    LuaArgument argModule, argFunction;
    try {
        argModule = lua.parseArgument(1, LuaArgumentType::LuaTypeString);
        argFunction = lua.parseArgument(2, LuaArgumentType::LuaTypeString);

    } catch (LuaException &exception) {
        Utilities::error(luaVm, exception.what());

        std::list<LuaArgument> returnArgs{-1, exception.what()};
        return lua.pushArguments(returnArgs.cbegin(), returnArgs.cend());
    }

    std::vector<LuaArgument> allArguments = lua.getArguments();

    int result = pythonCallInternal(
        argModule.toString(),
        argFunction.toString(),
        ArgumentList{allArguments.cbegin() + 2, allArguments.cend()}
    );
    lua.pushArgument(result);
    return 1;
}

