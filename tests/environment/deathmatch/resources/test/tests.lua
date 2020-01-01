local TEST_FUNCTIONS = {
    {
        name = "isPythonInited",
        description = "Checks Python VM initialization",
        input = { },
        expected = { true },
    },
    {
        name = "pythonCall",
        description = "Calls function from python",
        input = { "something" },
        expected = { -1, "Expected String" }
    },
    {
        name = "pythonCall",
        description = "Calls function from python",
        input = { "something", "call_function" },
        expected = { -1 }
    }
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
