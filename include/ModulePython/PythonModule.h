#pragma once

#include <Python.h>
#include <string>
#include <vector>


class PythonModule
{
public:
    explicit PythonModule() = default;

    PythonModule(const PythonModule &) = delete;
    PythonModule(PythonModule &&) = default;

    PythonModule &operator=(const PythonModule &) = delete;
    PythonModule &operator=(PythonModule &&) = default;

    /**
     * @brief Module documentation getter
     * @return String doc
     */
    const std::string &getModuleDoc() const
    {
        return this->moduleDoc;
    }

    /**
     * @brief Module name getter
     * @return String name
     */
    const std::string &getModuleName() const
    {
        return this->moduleName;
    }

    /**
     * @brief Methods getter
     * @return Vector of PyMethodDef
     */
    const std::vector<PyMethodDef> &getMethods() const
    {
        return this->methods;
    }

    /**
     * @brief Push new method
     * @param method Python method
     */
    void addMethod(const PyMethodDef &method)
    {
        this->methods.push_back(method);
    }

    /**
     * @brief Creates c-style methods array from methods vector.
     * @return C-style array
     */
    PyMethodDef *getMethodsArray() const;

    /**
     * @brief Created pointer to PyModuleDef object.
     * @return PyModuleDef pointer
     */
    virtual PyModuleDef *getModule() const;

    /**
     * @brief Module constructor
     */
    virtual void init()
    {
        this->moduleCreated = PyModule_Create(this->getModule());
    }

    /**
     * @brief Created module getter
     * @return PyObject pointer
     */
    PyObject *getModuleCreated() const
    {
        return this->moduleCreated;
    }

    virtual ~PythonModule() = default;

protected:
    // Main properties
    std::string moduleName;
    std::string moduleDoc;
    std::vector<PyMethodDef> methods;


    PyObject *moduleCreated = nullptr;
};