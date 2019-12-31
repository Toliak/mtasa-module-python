function echoTest()
    return "hello"
end

local TEST_FUNCTIONS = {
    {
        name = "echoTest",
        description = "echoTest TODO: change",
        input = { },
        expected = { "hello" },
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
