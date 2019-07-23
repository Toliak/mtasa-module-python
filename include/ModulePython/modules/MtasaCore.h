#pragma once

#include "ModulePython/PythonModule.h"
#include "ModulePython/commands/globalLuaVm.h"
#include "Modules.h"

namespace Modules
{

class MtasaCore: public PythonModule
{
public:
    static PyObject *callback(PyObject *self, PyObject *args)
    {
        Py_ssize_t pointer;

        if (!PyArg_ParseTuple(args, "n", &pointer)) {
            PyErr_SetString(PyExc_TypeError, "Parameter must be integer");
            return nullptr;
        }

        if (Commands::globalLuaVm) {
            LuaVmExtended lua(Commands::globalLuaVm);
            lua.call("callbackFromPython", {(int) pointer});
        }

        return PyLong_FromLong(pointer * 2);
    }

    void registerMethods()
    {
        this->addMethod({
                            "test",
                            &MtasaCore::callback,
                            METH_VARARGS,
                            "Test method"
                        });
    }

    void init() override
    {
        this->moduleName = "mtasa";

        this->registerMethods();

        PythonModule::init();
    }
};

extern "C" PyObject *mtasaCoreInit()
{
    auto module = new MtasaCore;
    module->init();
    initedModules.insert(module);

    return module->getModuleCreated();
}

}