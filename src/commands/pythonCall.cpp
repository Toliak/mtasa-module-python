#include <functional>
#include "ModulePython/modules/Modules.h"
#include "ModulePython/Exception.h"
#include "ModulePython/utilities.h"
#include "ModulePython/PythonVm.h"
#include "ModulePython/commands/globalLuaVm.h"
#include "ModulePython/commands/pythonCall.h"


using ArgumentList = std::list<LuaArgument>;

PyObject *parseForPython(const ArgumentList &arguments)
{
    PyObject *result = PyTuple_New(arguments.size());
    size_t index = 0;
    for (const LuaArgument &argument : arguments) {
        PyTuple_SetItem(result, index, Utilities::luaArgumentToPyObject(argument));
        ++index;
    }

    return result;
}

ArgumentList parseFromPython(PyObject *object)
{
    ArgumentList result{};

    if (PyTuple_Check(object)) {
        size_t size = PyTuple_Size(object);

        for (size_t i = 0; i < size; ++i) {
            PyObject *item = PyTuple_GetItem(object, i);
            result.push_back(std::move(Utilities::pyObjectToLuaArgument(item)));
        }

        return result;
    }

    result.push_back(std::move(Utilities::pyObjectToLuaArgument(object)));
    return result;
}
// TODO: provide passing userdata

// throws LuaUnexpectedType
ArgumentList pythonCallInternal(const std::string &moduleName,
                       const std::string &functionName,
                       const ArgumentList &arguments)
{
    // get python function

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
    if (!callable) {
        throw PythonFunctionNotFound{functionName, moduleName};
    }

    // prepare arguments

    PyObject *pythonArguments = parseForPython(arguments);

    // call function

    PyObject *functionResult = PyObject_CallObject(callable, pythonArguments);
    return parseFromPython(functionResult);
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

    try {
        auto resultList = pythonCallInternal(
            argModule.toString(),
            argFunction.toString(),
            ArgumentList{allArguments.cbegin() + 2, allArguments.cend()}
        );
        return lua.pushArguments(resultList.cbegin(), resultList.cend());;

    } catch (LuaException &exception) {
        Utilities::error(luaVm, exception.what());

        std::list<LuaArgument> returnArgs{-2, exception.what()};
        return lua.pushArguments(returnArgs.cbegin(), returnArgs.cend());
    } catch (PythonException &exception) {
        Utilities::error(luaVm, exception.what());

        std::list<LuaArgument> returnArgs{-3, exception.what()};
        return lua.pushArguments(returnArgs.cbegin(), returnArgs.cend());
    }
}

