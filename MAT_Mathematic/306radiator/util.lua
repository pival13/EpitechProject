local printObject; printObject = function (obj, indentSize)
    indentSize = indentSize or 0
    local s = ''
    for i = 1, indentSize do s = s .. ' ' end
    if type(obj) == "table" then
        print("{")
        for i, j in pairs(obj) do
            io.write(s .. '  ' .. tostring(i) .. ' = ')
            if j ~= obj and i ~= "package" then
                printObject(j, indentSize + 2)
            else
                print("this")
            end
        end
        print(s .. "}")
    else
        print(tostring(obj))
    end
end

return {
    printObject = printObject,
    --isMain = debug.getinfo(1, "S").short_src == arg[0]
}