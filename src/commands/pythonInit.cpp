#include <algorithm>
#include "ModulePython/commands/debug.h"
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

        Commands::debugInternal(
            Commands::globalLuaVm,
            {
                "Import ",
                name,
                std::to_string((uintptr_t) module)
            }
        );
    }
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

    } catch (LuaException &e) {
        debugInternal(luaVm, {e.what()});
    }

    int result = pythonInitUserModules(fileList);


    lua.pushArgument(result);

    return 1;
}