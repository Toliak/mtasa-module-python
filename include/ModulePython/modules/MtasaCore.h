#pragma once

#include "ModulePython/utilities.h"
#include "ModulePython/PythonModule.h"
#include "ModulePython/commands/globalLuaVm.h"
#include "Modules.h"

namespace Modules
{

class MtasaCore: public PythonModule
{
public:
    /**
     * @brief Method registration
     */
    void registerMethods();

    void init() override;
};

/**
 * @brief MtasaCore module initializer
 */
extern "C" PyObject *mtasaCoreInit();

}