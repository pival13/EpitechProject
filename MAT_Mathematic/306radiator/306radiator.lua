#! /usr/bin/env lua

local list = require 'listUtil'

local h = 0.5
local initValue = -300

local printMatrix = function (matrix)
    local size = #matrix
    local isTable = type(matrix[1]) == "table"

    for y = 1, size do
        if isTable then
            local size2 = #matrix[y]
            for x = 1, size2 do
                io.write(("%.02f%s"):format(matrix[y][x], x == size and "" or "\t"))
            end
            io.write("\n")
        else
            print(tostring(math.floor( matrix[y] * 10 + 0.5 ) / 10))
        end
    end
end

local createMatrix = function (size)
    local one = 1 / (h * h)
    local matrix = {}
    for y = 1, size * size do
        matrix[y] = {}
        for x = 1, size * size do
            if y <= size or y > size * (size - 1) or y % size == 0 or y % size == 1 then
                matrix[y][x] = y == x and 1 or 0
            elseif x == y then
                matrix[y][x] = -4 * one
            elseif x == y+1 or x == y-1 or x == y-size or x == y+size then
                matrix[y][x] = one
            else
                matrix[y][x] = 0
            end
        end
    end
    return matrix
end

local createResult = function (size, posX, posY)
    local matrix = {}
    for i = 1, size * size do
        matrix[i] = i-1 == posY * size + posX and initValue or 0
    end
    return matrix
end

local getInitMatrix = function (matrix, result)
    for pivot = 1, #matrix do
        for y = pivot + 1, #matrix do
            if matrix[y][pivot] ~= 0 then
                local n = matrix[y][pivot]
                for x = pivot, #matrix do
                    matrix[y][x] = matrix[y][x] - matrix[pivot][x] * n / matrix[pivot][pivot]
                end
                result[y] = result[y] - result[pivot] * n / matrix[pivot][pivot]
            end
        end
    end

    for pivot = #matrix, 1, -1 do
        if matrix[pivot][pivot] ~= 1 then
            result[pivot] = result[pivot] / matrix[pivot][pivot]
            matrix[pivot][pivot] = 1
        end
        for y = pivot - 1, 1, -1 do
            if matrix[y][pivot] ~= 0 then
                local n = matrix[y][pivot]
                for x = pivot, 1, -1 do
                    matrix[y][x] = matrix[y][x] - matrix[pivot][x] * n / matrix[pivot][pivot]
                end
                result[y] = result[y] - result[pivot] * n / matrix[pivot][pivot]
            end
        end
    end
    return result
end

if debug.getinfo(1, "S").short_src == arg[0] then
    if #arg ~= 3 and #arg ~= 5 then
        print("Invalid number of argument: Expected 3 or 5, got " .. tostring(#arg))
        os.exit(84)
    elseif list.any(arg, function (arg) return not arg:match("^%d+$") end) then
        print("Error: An argument is not a number")
        os.exit(84)
    end

    local size = tonumber(arg[1])
    local posX = tonumber(arg[2])
    local posY = tonumber(arg[3])
    if size <= 2 then
        print(("Size too small. Minimal value: 3"))
        os.exit(84)
    elseif posX <= 0 or posX >= size-1 or posY <= 0 or posY >= size-1 then
        print(("Position out of bound: (%d,%d) with size %dx%d (impossible to set on border)"):format(posX+1, posY+1, size, size))
        os.exit(84)
    end

    local matrix = createMatrix(size)
    local result = createResult(size, posX, posY)

    if #arg == 3 then
        printMatrix(matrix)
        print()
    end
    local init = getInitMatrix(matrix, result)
    if #arg == 3 then
        printMatrix(init)
    else
        posX = tonumber(arg[4])
        posY = tonumber(arg[5])
        if posX >= size or posY >= size then
            print(("Position out of bound: (%d,%d) with size %dx%d"):format(posX+1, posY+1, size, size))
            os.exit(84)
        end
        print(tostring(math.floor( init[posY * size + posX + 1] * 10 + 0.5 ) / 10))
    end
end