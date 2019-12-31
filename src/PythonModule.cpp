#include "ModulePython/PythonModule.h"

PyMethodDef *PythonModule::getMethodsArray() const
{
    const size_t arraySize = this->methods.size();
    auto methodsArray = new PyMethodDef[arraySize + 1];        // +1 for sentinel

    for (size_t i = 0; i < arraySize; i++) {
        methodsArray[i] = this->methods[i];
    }

    PyMethodDef sentinel{
        nullptr,
        nullptr,
        0,
        nullptr
    };
    methodsArray[arraySize] = sentinel;

    return methodsArray;
}

PyModuleDef *PythonModule::getModule() const
{
    auto module = new PyModuleDef{
        PyModuleDef_HEAD_INIT,
        this->moduleName.c_str(),   /* name of module */
        this->moduleDoc.c_str(), /* module documentation, may be NULL */
        -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
        this->getMethodsArray()
    };

    return module;
}
