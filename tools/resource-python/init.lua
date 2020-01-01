addEventHandler('onResourceStart', resourceRoot, function()
    if not USER_MODULES then
        outputDebugString('No files provided', 1)
        return false
    end

    pythonInit(FILES)
end)