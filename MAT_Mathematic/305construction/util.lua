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

local isMain = debug.getinfo( 1, 'S' ).sort_src == arg[0]

local readFile = function (path)
    local f, err = io.open(path, 'r')
    if err then print(err); return nil end
    return f:read("*all")
end

return {
    printObject = printObject,
    readFile = readFile
}