#pragma once

#include <Python.h>
#include <string>

class PythonVm
{
public:
    static const char *locale;          ///< Encode, decode locale. Default: UTF-8

    static PythonVm *getInstance();

    PythonVm(const PythonVm &) = delete;
    PythonVm(PythonVm &&) = delete;

    PythonVm &operator=(const PythonVm &) = delete;
    PythonVm &operator=(PythonVm &&) = delete;

    /**
     * @brief Python initializer
     * @warning Does not initialize python, if already have
     * @return Instance
     */
    static PythonVm *init(const std::wstring &programName = L"")
    {
        if (instance) {
            return instance;
        }

        instance = new PythonVm();
        if (!programName.empty()) {
            Py_SetProgramName(programName.c_str());
        }

        instance->initModules();
        instance->initPythonVm();
        return instance;
    }

private:
    PythonVm() = default;

    static PythonVm *instance;

    virtual void initModules();
    virtual void initPythonVm();
};