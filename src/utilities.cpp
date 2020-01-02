#include <functional>
#include <ModulePython/modules/Modules.h>
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

PyObject *luaObjectToPyObject(LuaArgument argument)
{
    const LuaObject &object = argument.extractObject();

    PyObject *constructor = Modules::getPythonFunction(
        "mtasa.element",
        "construct_element_by_id_and_name"
    );

    PyObject *result = PyObject_CallFunction(
        constructor,
        "ks",
        object.getObjectId().id,
        object.getStringClass().c_str()
    );

    return result;
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

LuaObject pyObjectToLuaObject(PyObject *object)
{
    struct ClassInfo
    {
        std::string moduleName;
        std::string className;
    };
    using ParserFunctionType = std::function<LuaObject(PyObject *)>;
    using ParserInnerType = std::pair<ClassInfo, ParserFunctionType>;
    static const std::list<ParserInnerType> parser{
        {
            {"mtasa.element", "Element"},
            [](PyObject *object) -> LuaObject {
                std::string typeName = Utilities::pythonTypeToString(object);
                PyObject *attrId = PyObject_GetAttrString(object, "_id");
                if (!attrId) {
                    throw PythonException{"Attribute _id not found in class mtasa.element.Element"};
                }

                unsigned long id = PyLong_AsUnsignedLong(attrId);
                return LuaObject{
                    ObjectId{id},
                    typeName
                };
            },
        },
    };

    for (const auto &pair: parser) {
        PyObject *pyClass = Modules::getPythonClass(pair.first.moduleName, pair.first.className);
        if (!PyObject_IsInstance(object, pyClass)) {
            continue;
        }
        return pair.second(object);
    }

    throw PythonUnexpectedType{Utilities::pythonTypeToString(object)};
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

std::string pythonTypeToString(PyObject *object)
{
    PyTypeObject *type = object->ob_type;
    return type->tp_name;
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
        {LuaArgumentType::LuaTypeUserdata, [](const LuaArgument &argument) -> PyObject * {
            return luaObjectToPyObject(argument);
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

    std::string typeName = pythonTypeToString(object);

    auto iterator = parser.find(typeName);
    if (iterator == parser.cend()) {
        return pyObjectToLuaObject(object);
    }

    return iterator->second(object);
}

}