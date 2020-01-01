#pragma once

#include <stdexcept>

class PythonException: public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

class PythonModuleNotFound: public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;

    explicit PythonModuleNotFound(const std::string &moduleName)
        : runtime_error("Module '" + moduleName +"' not found")
    {}
};

class PythonModuleNotImported: public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;

    explicit PythonModuleNotImported(const std::string &moduleName)
        : runtime_error("Module '" + moduleName +"' not imported")
    {}
};
