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
     * Module documentation getter
     */
    const std::string &getModuleDoc() const
    {
        return this->moduleDoc;
    }

    /**
     * Module name getter
     */
    const std::string &getModuleName() const
    {
        return this->moduleName;
    }

    /**
     * Methods getter
     */
    const std::vector<PyMethodDef> &getMethods() const
    {
        return this->methods;
    }

    /**
     * Push new method
     * @param method Python method
     */
    void addMethod(const PyMethodDef &method)
    {
        this->methods.push_back(method);
    }

    /**
     * Creates c-style methods array from methods vector.
     * Saves it in PythonModule object.
     * Destructs old array.
     * Will be destructed by destructor
     * @return array
     */
    PyMethodDef *getMethodsArray()
    {
        delete[] this->methodsArray;

        const size_t arraySize = this->methods.size();
        this->methodsArray = new PyMethodDef[arraySize + 1];        // +1 for sentinel

        for (size_t i = 0; i < arraySize; i++) {
            this->methodsArray[i] = this->methods[i];
        }

        PyMethodDef sentinel{
            nullptr,
            nullptr,
            0,
            nullptr
        };
        this->methodsArray[arraySize] = sentinel;

        return this->methodsArray;
    }

    /**
     * Created pointer to PyModuleDef object.
     * Saves it in PythonModule object.
     * Destructs old array.
     * Will be destructed by destructor
     * @return pointer
     */
    virtual PyModuleDef *getModule()
    {
        delete this->module;

        this->module = new PyModuleDef{
            PyModuleDef_HEAD_INIT,
            this->moduleName.c_str(),   /* name of module */
            this->moduleDoc.c_str(), /* module documentation, may be NULL */
            -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
            this->getMethodsArray()
        };

        return this->module;
    }

    /**
     * Module constructor
     */
    virtual void init()
    {
        this->moduleCreated = PyModule_Create(this->getModule());
    }

    PyObject *getModuleCreated() const
    {
        return this->moduleCreated;
    }

    virtual ~PythonModule()
    {
        delete[] this->methodsArray;
        delete this->module;
    }

protected:
    // Main properties
    std::string moduleName;
    std::string moduleDoc;
    std::vector<PyMethodDef> methods;

    // Destructable
    PyMethodDef *methodsArray = nullptr;
    PyModuleDef *module = nullptr;

    PyObject *moduleCreated = nullptr;
};