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
            PyErr_SetString(PyExc_TypeError, exception.what());
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

PyObject *methodMtasaCall(PyObject *self, PyObject *args)
{
    // check arguments

    size_t size = PyTuple_Size(args);
    if (size < 3) {
        PyErr_SetString(PyExc_TypeError, "Amount of parameters must be not less 3");
        return nullptr;
    }

    PyObject *pyMtasaObject = PyTuple_GetItem(args, 0);
    PyObject *pyElementClass = Modules::getPythonClass("mtasa.element", "Element");
    if (!PyObject_IsInstance(pyMtasaObject, pyElementClass)) {
        PyErr_SetString(PyExc_TypeError, "The first parameter must be an mtasa.element.Element");
        return nullptr;
    }

    PyObject *pyMethodName = PyTuple_GetItem(args, 1);
    if (!PyUnicode_Check(pyMethodName)) {
        PyErr_SetString(PyExc_TypeError, "The second parameter must be a string");
        return nullptr;
    }

    PyObject *pyReturnAmount = PyTuple_GetItem(args, 2);
    if (!PyLong_Check(pyReturnAmount)) {
        PyErr_SetString(PyExc_TypeError, "The third parameter must be a number");
        return nullptr;
    }

    // parse arguments

    std::list<LuaArgument> passArguments{};
    for (size_t i = 3; i < size; ++i) {
        try {
            passArguments.push_back(
                Utilities::pyObjectToLuaArgument(
                    PyTuple_GetItem(args, i)
                )
            );
        } catch (PythonException &exception) {
            PyErr_SetString(PyExc_TypeError, exception.what());
            return nullptr;
        }
    }

    int returnAmount = static_cast<int>(PyLong_AsLong(pyReturnAmount));
    LuaArgument element = Utilities::pyObjectToLuaArgument(pyMtasaObject);
    const char *cMethodName = PyBytes_AS_STRING(
        PyUnicode_AsEncodedString(pyMethodName, "utf-8", "~E~")
    );

    // call method

    LuaVmExtended lua(Commands::globalLuaVm);

    lua_getglobal(Commands::globalLuaVm, element.toObject().getStringClass().c_str());
    lua_getfield(Commands::globalLuaVm, -1, cMethodName);
//    lua_getglobal(Commands::globalLuaVm, "Element");
//    lua_getfield(Commands::globalLuaVm, -1, "getDimension");
    lua.pushArgument(element);

    lua_pcall(
        Commands::globalLuaVm,
        static_cast<int>(passArguments.size()) + 1,
        returnAmount,
        0
    );
    lua.pushArguments(passArguments.cbegin(), passArguments.cend());

    Utilities::iprint(Commands::globalLuaVm, {element, element.toObject().getStringClass(), cMethodName});
    Utilities::iprint(Commands::globalLuaVm, passArguments);

    // get method results

    std::vector<LuaArgument> resultArgs(static_cast<size_t>(returnAmount));
    for (int i = 0; i < returnAmount; i++) {
        int luaIndex = -returnAmount + i;
        resultArgs[i] = lua.parseArgument(luaIndex);
    }

    // parse lua arguments to py object

    PyObject *result = PyTuple_New(returnAmount);
    size_t index = 0;
    for (const LuaArgument &argument : resultArgs) {
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
    this->addMethod({
                        "_mtasa_call_method",
                        methodMtasaCall,
                        METH_VARARGS,
                        "Call method from MTASA Lua"
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
