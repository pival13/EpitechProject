local printObject; printObject = function (obj, indentSize)
    indentSize = indentSize or 0
    local s = ''
    for i = 1, indentSize do s = s .. ' ' end
    if type(obj) == "table" then
        print("{")
        for i, j in pairs(obj) do
            io.write(s .. '  ' .. tostring(i) .. ' = ')
            printObject(j, indentSize + 2)
        end
        print(s .. "}")
    else
        print(tostring(obj))
    end
end

local failure = function (s)
    io.stderr:write(s .. "\n")
    os.exit(84)
end

return {
    printObject = printObject,
    failure = failure,
    --isMain = debug.getinfo(1, "S").short_src == arg[0]
}