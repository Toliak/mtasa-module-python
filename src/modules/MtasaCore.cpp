#include "ModulePython/modules/MtasaCore.h"

PyObject *callback(PyObject *self, PyObject *args)
{
    char *cString = nullptr;

    if (!PyArg_ParseTuple(args, "s", &cString)) {
        PyErr_SetString(PyExc_TypeError, "Parameter must be string");
        return nullptr;
    }

    if (Commands::globalLuaVm) {
        LuaVmExtended lua(Commands::globalLuaVm);

        std::string string{cString};
        lua.call("callbackFromPython", {string});
    }

    return nullptr;
}

namespace Modules
{

void MtasaCore::registerMethods()
{
    this->addMethod({
                        "test",
                        callback,
                        METH_VARARGS,
                        "Test method"
                    });
}

void MtasaCore::init()
{
    this->moduleName = "mtasa";

    this->registerMethods();

    PythonModule::init();
}

PyObject *mtasaCoreInit()
{
    auto module = new MtasaCore;
    module->init();
    initedModules.insert(module);

    return module->getModuleCreated();
}

}
