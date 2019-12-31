#pragma once

#include <Python.h>
#include <string>

class PythonVm
{
public:
    static const char *locale;          ///< Encode, decode locale. Default: UTF-8

    /**
     * @brief Instance getter
     * @return Instance pointer if exists, nullptr otherwise
     */
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
     * @return Instance
     */
    static PythonVm *init(
        const std::wstring &programName = L"",
        const std::wstring &pythonPath = L"",
        const std::wstring &pythonHome = L""
    );

    /**
     * @brief Global dictionary getter
     * @return PyObject pointer to dictionary
     */
    PyObject *getGlobalDictionary() const
    {
        return globalDictionary;
    }

    /**
     * @brief Main module getter
     * @return PyObject pointer to module
     */
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