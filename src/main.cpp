#include "ModulePython/PythonVm.h"
#include "ModulePython/commands.h"
#include "ModulePython/modules/MtasaCore.h"
#include "lua/ILuaModuleManager.h"
#include "lua/LuaImports.h"
#include <cstring>

#define MODULE_NAME "ModulePython"
#define MODULE_AUTHOR "Toliak"
#define MODULE_VERSION 1.02f

ILuaModuleManager10 *pModuleManager = nullptr;          ///< Global module manager

bool ms_bInitWorked = false;                            ///< Initialization flag

// Initialisation function (module entrypoint)
EXTERN_C bool InitModule(ILuaModuleManager10 *pManager, char *szModuleName, char *szAuthor, float *fVersion)
{
    pModuleManager = pManager;

    // Set the module info
    strncpy(szModuleName, MODULE_NAME, MAX_INFO_LENGTH);
    strncpy(szAuthor, MODULE_AUTHOR, MAX_INFO_LENGTH);
    (*fVersion) = MODULE_VERSION;

#ifndef WIN32
    if (!ImportLua()) {
        return false;
    }
#endif

    ms_bInitWorked = true;

    {           // Init modules
        PyImport_AppendInittab("_mtasa_core", Modules::mtasaCoreInit);
    }

    PythonVm::init();

    // TODO: move to init
    const wchar_t *pythonPath = L"mods/deathmatch/python/__init__.py";
    wchar_t *pyArgv[] = {const_cast<wchar_t *>(pythonPath)};
    PySys_SetArgv(
        1,
        pyArgv
    );

    return true;
}


EXTERN_C void RegisterFunctions(lua_State *luaVm)
{
    if (!ms_bInitWorked) {
        return;
    }
    if (!(pModuleManager && luaVm)) {
        return;
    }

    pModuleManager->RegisterFunction(luaVm, "pythonInit", Commands::pythonInit);
    pModuleManager->RegisterFunction(luaVm, "isPythonInited", Commands::isPythonInited);
    pModuleManager->RegisterFunction(luaVm, "pythonCallback", Commands::pythonCallback);
    pModuleManager->RegisterFunction(luaVm, "pythonTriggerEvent", Commands::pythonTriggerEvent);
}

EXTERN_C bool DoPulse()
{
    return true;
}


EXTERN_C void ResourceStopped(lua_State *)
{

}


EXTERN_C bool ShutdownModule(void)
{
    Py_Finalize();

    for (PythonModule *module: Modules::initedModules) {
        delete module;
    }

    return true;
}
