local TEST_FUNCTIONS = {
    {
        name = "isPythonInited",
        description = "Checks Python VM initialization",
        input = { },
        expected = { true },
    },
}

addEventHandler("onResourceStart", resourceRoot, function()
    iprint('===============[ TESTING START ]===============')

    for _, v in pairs(TEST_FUNCTIONS) do
        addTest(v.name)
    end

    for _, v in pairs(TEST_FUNCTIONS) do
        runTest(
                v.name,
                v.input or {},
                v.expected,
                v.description or ""
        )
    end

    testStatus()

    iprint('===============[ TESTING END ]===============')
end)
