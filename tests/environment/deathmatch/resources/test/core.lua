TestsInfo = {
    total = 0,
    success = 0
}
Tests = {}

function addTest(name)
    Tests[name] = _G[name]
end

function checkTable(left, right)
    if #left ~= #right then
        return false
    end

    for i, v in pairs(left) do
        if type(v) == 'table' then
            if not checkTable(v, right[i]) then
                return false
            end
        elseif v ~= right[i] then
            return false
        end
    end
    return true
end

function runTest(name, input, excepted, description)
    TestsInfo.total = TestsInfo.total + 1
    iprint('===============[ TEST ]===============')
    iprint(description .. " (" .. name .. ")")

    local result = { Tests[name](unpack(input)) }
    local status = checkTable(result, excepted)
    TestsInfo.success = TestsInfo.success + (status and 1 or 0)
    if status then
        iprint("Test success")
    else
        iprint("Test failed. Expected: ", excepted, "Got: ", result)
    end
end

function testStatus()
    iprint('===============[ TOTAL ]===============')
    if TestsInfo.total == TestsInfo.success then
        iprint("[TEST TOTAL][OK] Tests passed " .. TestsInfo.success .. "/" .. TestsInfo.total)
        iprint("[TEST TOTAL][OK] All tests passed!")
    else
        iprint("[TEST TOTAL][ER] Tests passed " .. TestsInfo.success .. "/" .. TestsInfo.total)
    end
end
