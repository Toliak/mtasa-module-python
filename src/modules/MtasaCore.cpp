#include "ModulePython/Exception.h"
#include "ModulePython/modules/MtasaCore.h"

PyObject *functionMtasaCall(PyObject *self, PyObject *args)
{
    char *cString = nullptr;

    // check arguments

    size_t size = PyTuple_Size(args);
    if (size < 2) {
        PyErr_SetString(PyExc_TypeError, "Amount of parameters must be not less 2");
        return nullptr;
    }

    PyObject *pyFunctionName = PyTuple_GetItem(args, 0);
    if (!PyUnicode_Check(pyFunctionName)) {
        PyErr_SetString(PyExc_TypeError, "The first parameter must be a string");
        return nullptr;
    }

    PyObject *pyReturnAmount = PyTuple_GetItem(args, 1);
    if (!PyLong_Check(pyReturnAmount)) {
        PyErr_SetString(PyExc_TypeError, "The second parameter must be a number");
        return nullptr;
    }

    // parse arguments

    std::list<LuaArgument> passArguments{};
    for (size_t i = 2; i < size; ++i) {
        try {
            passArguments.push_back(
                Utilities::pyObjectToLuaArgument(
                    PyTuple_GetItem(args, i)
                )
            );
        } catch (PythonException &exception) {
            PyErr_SetString(PyExc_TypeError, "The first parameter must be a number");
            return nullptr;
        }
    }

    int returnAmount = static_cast<int>(PyLong_AsLong(pyReturnAmount));
    const char *cFunctionName = PyBytes_AS_STRING(
        PyUnicode_AsEncodedString(pyFunctionName, "utf-8", "~E~")
    );

    // call function

    LuaVmExtended lua(Commands::globalLuaVm);
    std::vector<LuaArgument> returned;
    try {
        returned = lua.call(
            cFunctionName,
            passArguments,
            returnAmount
        );
    } catch (LuaException &exception) {
        PyErr_SetString(PyExc_EnvironmentError, exception.what());
        return nullptr;
    }

    // parse lua arguments to py object

    PyObject *result = PyTuple_New(returned.size());
    size_t index = 0;
    for (const LuaArgument &argument : returned) {
        PyTuple_SetItem(result, index, Utilities::luaArgumentToPyObject(argument));
        ++index;
    }
    return result;
}

namespace Modules
{

void MtasaCore::registerMethods()
{
    this->addMethod({
                        "_mtasa_call",
                        functionMtasaCall,
                        METH_VARARGS,
                        "Call function from MTASA Lua"
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
