#pragma once

#include <Python.h>
#include <string>

class PythonVm
{
public:
    static const char *locale;          ///< Encode, decode locale. Default: UTF-8

    static PythonVm *getInstance()
    {
        return PythonVm::instance;
    }

    PythonVm(const PythonVm &) = delete;
    PythonVm(PythonVm &&) = delete;

    PythonVm &operator=(const PythonVm &) = delete;
    PythonVm &operator=(PythonVm &&) = delete;

    /**
     * @brief Python initializer
     * @warning Does not initialize python, if already have
     * @return Instance
     */
    static PythonVm *init(
        const std::wstring &programName = L"",
        const std::wstring &pythonPath = L"",
        const std::wstring &pythonHome = L""
    );

    PyObject *getGlobalDictionary() const
    {
        return globalDictionary;
    }

    PyObject *getMainModule() const
    {
        return mainModule;
    }

private:
    PythonVm() = default;

    static PythonVm *instance;                       ///< Singleton instance

    virtual void initPythonVm();

    PyObject *globalDictionary = nullptr;            ///< Python's global dictionary
    PyObject *mainModule = nullptr;                  ///< Python's main module
};