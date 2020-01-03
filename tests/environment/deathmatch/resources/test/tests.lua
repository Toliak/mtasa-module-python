local MODULES = {
    'mtasa.core',
    'mtasa.element',
    'mtasa.event',
    'mtasa.exception',
    'main',
    'element_test',
    'call_functions',
}

local TEST_ELEMENT = Vehicle(400, 0, 0, 0)
local TEST_VECTOR = Vector3(5,8,10)

local TEST_FUNCTIONS = {
    {
        name = "isPythonInited",
        description = "Checks Python VM initialization (true)",
        input = { },
        expected = { true },
    },
    {
        name = "pythonDestroy",
        description = "Destroy python VM",
        input = { },
        expected = { },
    },
    {
        name = "isPythonInited",
        description = "Checks Python VM initialization (false)",
        input = {  },
        expected = { false },
    },
    {
        name = "pythonInit",
        description = "Init python VM",
        input = { MODULES },
        expected = { #MODULES },
    },
    {
        name = "isPythonInited",
        description = "Checks Python VM initialization (true)",
        input = { },
        expected = { true },
    },
    {
        name = "pythonCall",
        description = "pythonCall with wrong arguments 0",
        input = {  },
        expected = { -1, "Expected String" },
    },
    {
        name = "pythonCall",
        description = "pythonCall with wrong arguments 1",
        input = { "something" },
        expected = { -1, "Expected String" },
    },
    {
        name = "pythonCall",
        description = "Calls not existing function from python",
        input = { "call_functions", "__not_existing_function__" },
        expected = { -3, "Function '__not_existing_function__' in module 'call_functions' not found" },
    },
    {
        name = "pythonCall",
        description = "Calls string check function in python",
        input = { "call_functions", "accept_string", "definitely a string" },
        expected = { true },
    },
    {
        name = "pythonCall",
        description = "Calls string check function in python with number",
        input = { "call_functions", "accept_string", 123 },
        expected = { false },
    },
    {
        name = "pythonCall",
        description = "Calls number check function in python",
        input = { "call_functions", "accept_number", 574.6 },
        expected = { true },
    },
    {
        name = "pythonCall",
        description = "Calls map (dict) check function in python",
        input = { "call_functions", "accept_map", { a = 1, b = 4 } },
        expected = { true },
    },
    {
        name = "pythonCall",
        description = "Calls map (dict) check function in python (with nested tables)",
        input = { "call_functions", "accept_map", { list_here = { 3, 2, 1 }, [1] = "aa" } },
        expected = { true },
    },
    {
        name = "pythonCall",
        description = "Calls echo with number",
        input = { "call_functions", "echo", 1509 },
        expected = { 1509 },
    },
    {
        name = "pythonCall",
        description = "Calls echo with string",
        input = { "call_functions", "echo", "i am string" },
        expected = { "i am string" },
    },
    {
        name = "pythonCall",
        description = "Calls echo with multiple arguments",
        input = { "call_functions", "echo", "arg1", "arg2", 3, false },
        expected = { "arg1", "arg2", 3, false },
    },
    {
        name = "pythonCall",
        description = "Calls echo with list",
        input = { "call_functions", "echo", { 1, 2, "str 3", 4 } },
        expected = { { 1, 2, "str 3", 4 } },
    },
    {
        name = "pythonCall",
        description = "Calls echo with list with nested tables",
        input = { "call_functions", "echo", { 1, { i = 2, j = "str 3" }, 4 } },
        expected = { { 1, { i = 2, j = "str 3" }, 4 } },
    },
    {
        name = "pythonCall",
        description = "Calls echo with resourceRoot",
        input = { "call_functions", "echo", resourceRoot },
        expected = { resourceRoot },
    },
    {
        name = "pythonCall",
        description = "Calls echo with root",
        input = { "call_functions", "echo", root },
        expected = { root },
    },
    {
        name = "pythonCall",
        description = "Calls callback function",
        input = { "call_functions", "callback", TEST_ELEMENT },
        expected = { TEST_ELEMENT },
    },
    {
        name = "pythonCall",
        description = "Calls exception throwing function",
        input = { "call_functions", "throw_exception" },
        expected = {
            -3,
            "Type: <class 'RuntimeError'>\n"
                    .. "Message: Test error\n"
                    .. "Traceback: \n"
                    .. "  File \"mods/deathmatch/python/call_functions.py\", line 32, in throw_exception\n"
                    .. "    raise RuntimeError(\"Test error\")"
        },
    },
    {
        name = "pythonCall",
        description = "Calls callback function that calls element method",
        input = { "call_functions", "call_element_method_dimension", TEST_ELEMENT },
        expected = { 0 },
    },
}

function callbackFromPython(arg)
    iprint('Callback here. With ', arg)

    return arg
end

addEventHandler("onResourceStart", resourceRoot, function()
    iprint('===============[ TESTING START ]===============')

    for _, v in ipairs(TEST_FUNCTIONS) do
        addTest(v.name)
    end

    for _, v in ipairs(TEST_FUNCTIONS) do
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
