addEventHandler('onResourceStart', resourceRoot, function()
    if not USER_MODULES then
        outputDebugString('No files provided', 1)
        return false
    end

    allModules = {}
    for _, v in ipairs(CORE_MODULES) do
        table.insert(allModules, v)
    end
    for _, v in ipairs(USER_MODULES) do
        table.insert(allModules, v)
    end

    pythonInit(allModules)
end)