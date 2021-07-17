#! /usr/bin/env lua

local List = require 'listUtil'
local Dict = require 'dictUtil'

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

local displayMatrix2 = function (mat)
    for _, line in ipairs(mat) do
        for i, elem in ipairs(line) do
            io.write((i == 1 and '' or ' ') .. tostring(elem))
        end
        print("")
    end
end

local usage = function (bin)
    print('USAGE:')
    print(string.format("\t%s file [n | p1 p2]", bin))
    print('DESCRIPTION')
    print('\tfile\tfile that contains the list of Facebook connections')
    print('\tn\tmaximum length of the paths')
    print('\tpi\tname of someone in the file')
end

local readFile = function (file)
    local file, error = io.open(file)
    if error then print(error); os.exit(84) end

    local relations = {}
    for line in file:lines() do
        local name1, name2 = line:match('^(.-) is friends with (.+)$')
        if not name1 or not name2 then print("Invalid line format"); os.exit(84) end
        if relations[name1] then
            table.insert(relations[name1], name2)
        else
            relations[name1] = { name2 }
        end
        if relations[name2] then
            table.insert(relations[name2], name1)
        else
            relations[name2] = { name1 }
        end
    end
    
    persons = Dict.keys(relations)
    table.sort(persons)
    relationships = {}
    for i, pers in ipairs(persons) do
        relationships[i] = {}
        for j, pers2 in ipairs(persons) do
            relationships[i][j] = List.any(relations[pers], function (s) return s == pers2 end) and 1 or 0
        end
    end
    return persons, relationships
end

local matrixShortestPath = function (matrix, maxLen)
    maxLen = maxLen or #matrix
    mat = {}
    for i = 1, #matrix do
        mat[i] = {}
        for j = 1, #matrix do
            mat[i][j] = matrix[i][j] > 0 and 1 or 0
        end
        mat[i][i] = 0
    end
    for iter = 1, math.ceil(math.sqrt(maxLen)) do
        local mat2 = {}
        for i = 1, #matrix do
            mat2[i] = {}
            for j = 1, #matrix do
                mat2[i][j] = mat[i][j]
                    for k = 1, #matrix do
                        if i ~= j and mat[i][k] ~= 0 and mat[k][j] ~= 0 and mat[i][k] + mat[k][j] <= maxLen then
                            mat2[i][j] = mat2[i][j] == 0 and (mat[i][k]+mat[k][j]) or math.min(mat2[i][j], mat[i][k]+mat[k][j])
                        end
                    end
            end
        end
        mat = mat2
    end
    return mat
end

local matrixPart = function (persons, relations, maxLen)
    for _, name in ipairs(persons) do print(name) end
    print()
    displayMatrix2(relations)
    print()
    displayMatrix2(matrixShortestPath(relations, maxLen))
end

local findLink = function (persons, relations, p1, p2)
    io.write('Degree of separation between '..p1..' and '..p2..': ')
    index1 = List.find(persons, p1)
    index2 = List.find(persons, p2)
    if not index1 or not index2 then
        print(-1)
    else
        local mat = matrixShortestPath(relations)
        print(mat[index1][index2])
    end
end

local main = function (args)
    if not (#args == 2 and args[2]:match('^%d+$')) and #args ~= 3 then usage(args[0]); os.exit(84) end
    
    local persons, relations = readFile(args[1])
    if #args == 2 then
        matrixPart(persons, relations, tonumber(args[2]))
    else
        findLink(persons, relations, args[2], args[3])
    end
end

return main(arg)