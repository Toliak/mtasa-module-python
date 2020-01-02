#include <algorithm>
#include "ModulePython/modules/Modules.h"
#include "ModulePython/Exception.h"
#include "ModulePython/utilities.h"
#include "ModulePython/PythonVm.h"
#include "ModulePython/commands/globalLuaVm.h"
#include "ModulePython/commands/pythonInit.h"


using ModuleNameList = std::list<std::string>;

int pythonInitUserModules(const ModuleNameList &moduleNames)
{
    // load provided modules
    for (const auto &name: moduleNames) {
        PyObject *pythonName = PyUnicode_FromString(name.c_str());
        PyObject *module = PyImport_Import(pythonName);

        if (!module) {
            if (PyErr_Occurred()) {
                Utilities::pythonCaptureException();
            }

            throw PythonModuleNotFound{name};
        }

        Modules::userModules.emplace(name, module);
    }

    return moduleNames.size();
}

int Commands::pythonInit(lua_State *luaVm)
{
    updateGlobalLuaVm(luaVm);
    LuaVmExtended lua(luaVm);

    ModuleNameList fileList;

    try {
        // Argument
        auto luaFileListArg = lua.parseArgument(1, LuaArgumentType::LuaTypeTableMap);

        // Vector of LuaArguments
        auto luaFileList = luaFileListArg.toList();

        std::transform(luaFileList.cbegin(),
                       luaFileList.cend(),
                       std::back_inserter(fileList),
                       [](const LuaArgument &arg) {
                           return arg.toString();
                       });

    } catch (LuaException &exception) {
        Utilities::error(luaVm, exception.what());

        std::list<LuaArgument> returnArgs{-1, exception.what()};
        return lua.pushArguments(returnArgs.cbegin(), returnArgs.cend());
    }

    PythonVm::init();

    try {
        int result = pythonInitUserModules(fileList);
        lua.pushArgument(result);
        return 1;

    } catch (PythonException &exception) {
        Utilities::error(luaVm, exception.what());

        std::list<LuaArgument> returnArgs{-2, exception.what()};
        return lua.pushArguments(returnArgs.cbegin(), returnArgs.cend());
    }
}