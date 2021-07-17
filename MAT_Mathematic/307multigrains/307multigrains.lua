#! /usr/bin/env lua

local list = require 'listUtil'
local util = require "util"

local matrixProduction = {
    {1, 1, 2, 0},
    {0, 2, 1, 0},
    {1, 0, 0, 3},
    {0, 1, 1, 1},
    {2, 0, 0, 2}
}

local printMatrix = function (matrix)
    local size = #matrix
    local isTable = type(matrix[1]) == "table"

    print()
    for y = 1, size do
        if isTable then
            local size2 = #matrix[y]
            for x = 1, size2 do
                io.write(("%s%s"):format(matrix[y][x], x == size2 and "" or "\t"))
            end
            io.write("\n")
        else
            print(tostring(math.floor( matrix[y] * 10 + 0.5 ) / 10))
        end
    end
end

local resolve307 = function (tbl)
    local lastLine = tbl[#tbl]

    while list.any(lastLine, function (v) return v < 0 end) do
        local col = list.min(lastLine)
        local row = list.min(tbl, function (line1, line2)
            if line1[col] <= 0 then return false
            elseif line2[col] <= 0 then return true
            else return line1[#line1] / line1[col] < line2[#line2] / line2[col] end
        end)
        local divider = tbl[row][col]
        for j = 1, #tbl[row] do
            tbl[row][j] = tbl[row][j] / divider
        end
        for i = 1, #tbl do if i ~= row then
            local mult = tbl[i][col]
            for j = 1, #tbl[i] do
                tbl[i][j] = tbl[i][j] - mult * tbl[row][j]
            end
        end end
    end
end

local createMatrix307 = function (args)
    local tbl = {}
    local nbEquat = #matrixProduction[1]
    local nbVar = #matrixProduction

    for i = 1, nbEquat do
        tbl[i] = {}
        for j = 1, nbVar do
            tbl[i][j] = matrixProduction[j][i]
        end
        --for j = 1, nbEquat do
        --    tbl[i][nbVar+j] = j == i and 1 or 0
        --end
        tbl[i][nbVar--[[+nbEquat]]+1] = tonumber(args[i])
    end

    tbl[nbEquat+1] = {}
    for j = 1, nbVar do
        tbl[nbEquat+1][j] = -tonumber(args[nbEquat + j])
    end
    --for j = 1, nbEquat do 
    --    tbl[nbEquat+1][nbVar+j] = 0
    --end
    tbl[nbEquat+1][nbVar--[[+nbEquat]]+1] = 0

    return tbl
end

local getValue307 = function (tbl, i)
    if tbl[5][i] ~= 0 then return "0"
    else
        local v = tbl[list.find_if(tbl, function (line) return line[i] == 1 end)][6]
        if v == 0 then return "0"
        else return ("%.02f"):format(v) end
    end
end

if debug.getinfo(1, "S").short_src == arg[0] then
    if #arg ~= 9 then util.failure("Not enough parameters: 9 expected, got " .. tostring(#arg)) end
    if list.any(arg, function (s) return not s:match("^%s*%d+%s*$") end) then util.failure("All parameters must be numbers") end

    local tbl = createMatrix307(arg)--{8, 12, 2, 3})
    resolve307(tbl)

    print(("Resources: %d F1, %d F2, %d F3, %d F4"):format(arg[1], arg[2], arg[3], arg[4]))
    print()
    print(("Oat: %s units at $%d/unit"):format(getValue307(tbl, 1), arg[5]))
    print(("Wheat: %s units at $%d/unit"):format(getValue307(tbl, 2), arg[6]))
    print(("Corn: %s units at $%d/unit"):format(getValue307(tbl, 3), arg[7]))
    print(("Barley: %s units at $%d/unit"):format(getValue307(tbl, 4), arg[8]))
    print(("Soy: %s units at $%d/unit"):format(getValue307(tbl, 5), arg[9]))
    print()
    print(("Total production value: $%.02f"):format(tbl[5][6]))
end
