#include <functional>
#include "ModulePython/Exception.h"
#include "ModulePython/commands/globalLuaVm.h"
#include "ModulePython/utilities.h"

PyObject *luaTableMapToPyObject(const LuaArgument &argument)
{
    using ResolverFunction = std::function<PyObject *(const LuaArgument &)>;
    static const std::unordered_map<LuaArgumentType, ResolverFunction> resolverKeys{
        {LuaArgumentType::LuaTypeString, [](const LuaArgument &argument) -> PyObject * {
            return Py_BuildValue("s", argument.toString().c_str());
        }},
        {LuaArgumentType::LuaTypeNumber, [](const LuaArgument &argument) -> PyObject * {
            return Py_BuildValue("d", argument.toNumber());
        }},
    };

    // transformation

    try {       // let's try to put list
        const auto &list = argument.toList();
        PyObject *pythonList = PyList_New(list.size());

        size_t index = 0;
        for (const auto &arg: list) {
            PyObject *value = Utilities::luaArgumentToPyObject(arg);
            PyList_SetItem(pythonList, index++, value);
        }

        return pythonList;
    } catch (LuaCannotTransformArgumentToList &) {
        // ok, put map
    }

    const auto &map = argument.toMap();
    PyObject *dict = PyDict_New();

    for (const auto &pair: map) {
        auto keyIterator = resolverKeys.find(pair.first.getType());
        if (keyIterator == resolverKeys.cend()) {
            throw LuaUnexpectedType{};
        }

        PyObject *key = keyIterator->second(pair.first);
        PyObject *value = Utilities::luaArgumentToPyObject(pair.second);
        PyDict_SetItem(dict, key, value);
    }

    return dict;
}

LuaArgument::TableListType pyListToLuaTable(PyObject *object)
{
    LuaArgument::TableListType result{};

    size_t size = PyList_Size(object);
    for (size_t i = 0; i < size; ++i) {
        PyObject *item = PyList_GetItem(object, i);
        result.push_back(std::move(Utilities::pyObjectToLuaArgument(item)));
    }
    return result;
}

LuaArgument::TableMapType pyDictToLuaTable(PyObject *object)
{
    LuaArgument::TableMapType result{};

    PyObject *keys = PyDict_Keys(object);
    size_t keysSize = PyList_Size(keys);

    for (size_t i = 0; i < keysSize; ++i) {
        PyObject *key = PyList_GetItem(keys, i);
        PyObject *value = PyDict_GetItem(object, key);

        result.emplace(
            Utilities::pyObjectToLuaArgument(key),
            Utilities::pyObjectToLuaArgument(value)
        );
    }
    return result;
}

namespace Utilities
{

void iprint(lua_State *luaVm, const std::list<LuaArgument> &args)
{
    LuaVmExtended lua(luaVm);

    lua.call("iprint", args);
}

void error(lua_State *luaVm, const std::string &errorMessage)
{
    LuaVmExtended lua(luaVm);

    lua.call("outputDebugString", {errorMessage, 1});
}

std::string pythonObjectToString(PyObject *object)
{
    PyObject *repr = PyObject_Repr(object);
    PyObject *str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
    const char *bytes = PyBytes_AS_STRING(str);

    return bytes;
}

PyObject *luaArgumentToPyObject(const LuaArgument &argument)
{
    using ParserFunctionType = std::function<PyObject *(const LuaArgument &)>;
    static const std::unordered_map<LuaArgumentType, ParserFunctionType> parser{
        {LuaArgumentType::LuaTypeString, [](const LuaArgument &argument) -> PyObject * {
            return Py_BuildValue("s", argument.toString().c_str());
        }},
        {LuaArgumentType::LuaTypeNumber, [](const LuaArgument &argument) -> PyObject * {
            return Py_BuildValue("d", argument.toNumber());
        }},
        {LuaArgumentType::LuaTypeBoolean, [](const LuaArgument &argument) -> PyObject * {
            return argument.toBool() ? Py_True : Py_False;
        }},
        {LuaArgumentType::LuaTypeTableMap, [](const LuaArgument &argument) -> PyObject * {
            return luaTableMapToPyObject(argument);
        }},
    };

    auto iterator = parser.find(argument.getType());
    if (iterator == parser.cend()) {
        throw LuaUnexpectedType{};
    }

    return iterator->second(argument);
}

LuaArgument pyObjectToLuaArgument(PyObject *object)
{
    using ParserFunctionType = std::function<LuaArgument(PyObject *)>;
    static const std::unordered_map<std::string, ParserFunctionType> parser{
        {"str", [](PyObject *object) -> LuaArgument {
            PyObject *byteArray = PyUnicode_AsEncodedString(object, "utf-8", "~E~");
            const char *cString = PyBytes_AS_STRING(byteArray);

            return LuaArgument(cString);
        }},
        {"int", [](PyObject *object) -> LuaArgument {
            return LuaArgument(static_cast<int>(PyLong_AsLong(object)));
        }},
        {"float", [](PyObject *object) -> LuaArgument {
            return LuaArgument(PyFloat_AsDouble(object));
        }},
        {"bool", [](PyObject *object) -> LuaArgument {
            return LuaArgument(static_cast<bool>(PyObject_IsTrue(object)));
        }},
        {"list", [](PyObject *object) -> LuaArgument {
            return pyListToLuaTable(object);
        }},
        {"dict", [](PyObject *object) -> LuaArgument {
            return pyDictToLuaTable(object);
        }},
    };

    PyTypeObject *type = object->ob_type;
    const char *cTypeName = type->tp_name;

    auto iterator = parser.find(cTypeName);
    if (iterator == parser.cend()) {
        throw PythonUnexpectedType{cTypeName};
    }

    return iterator->second(object);
}

}