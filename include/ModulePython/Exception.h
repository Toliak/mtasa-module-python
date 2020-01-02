#pragma once

#include <stdexcept>

class PythonException: public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class PythonModuleNotFound: public PythonException
{
public:
    using PythonException::PythonException;

    explicit PythonModuleNotFound(const std::string &moduleName)
        : PythonException("Module '" + moduleName + "' not found")
    {}
};

class PythonModuleNotImported: public PythonException
{
public:
    using PythonException::PythonException;

    explicit PythonModuleNotImported(const std::string &moduleName)
        : PythonException("Module '" + moduleName + "' not imported")
    {}
};

class PythonFunctionNotFound: public PythonException
{
public:
    using PythonException::PythonException;

    explicit PythonFunctionNotFound(const std::string &functionName)
        : PythonException("Function '" + functionName + "' not found")
    {}

    PythonFunctionNotFound(const std::string &functionName, const std::string &moduleName)
        : PythonException("Function '" + functionName + "' in module '" + moduleName + "' not found")
    {}
};

class PythonUnexpectedType: public PythonException
{
public:
    using PythonException::PythonException;

    explicit PythonUnexpectedType()
        : PythonException("Unexpected type")
    {}

    explicit PythonUnexpectedType(const std::string &typeName)
        : PythonException("Unexpected type '" + typeName +  "'")
    {}
};
