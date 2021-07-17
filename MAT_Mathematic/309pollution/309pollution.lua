#! /usr/bin/env lua

local list = require 'listUtil'
local exit = require 'util'.failure

local count = 0
--[=[
local __expo = {[0] = 1}
local __getExpo; __getExpo = function (m)
    if __expo[m] then return __expo[m] end
    local v = __getExpo(m-1) * m
    __expo[m] = v
    count = count + 1
    return v
end
local coeffBino = function (k, m)
    for i = 1, m do
        if not __expo[i] then __expo[i] = __expo[i-1] * i end
    end
    return __expo[m] / (__expo[k] * __expo[m-k])
end


local __bernsteinPoly = {}
local bernsteinPoly = function (k, m, t)
    if not __bernsteinPoly[m] then
        __bernsteinPoly[m] = {}
    end
    if not __bernsteinPoly[m][k] then
        __bernsteinPoly[m][k] = {}
    end
    if not __bernsteinPoly[m][k][t] then
        count = count + 1
        __bernsteinPoly[m][k][t] = coeffBino(k, m) * math.pow(t, k) * math.pow(1-t, m-k)
        --print(("Bernstein with k=%d, m=%d, t=%f ==> %f"):format(k, m, t, __bernsteinPoly[m][k][t]))
    end
    return __bernsteinPoly[m][k][t]
end
]=]
local __bernsteinPolyCastel = {}
local bernsteinPolyCasteljau = function (k, m, t)
    for mm = 0, m do
        if not __bernsteinPolyCastel[mm] then __bernsteinPolyCastel[mm] = {} end
        for kk = math.max(k-m+mm, 0), math.min(mm, k) do
            if not __bernsteinPolyCastel[mm][kk] then __bernsteinPolyCastel[mm][kk] = {} end
            if not __bernsteinPolyCastel[mm][kk][t] then
                if mm == 0 and kk == 0 then
                    __bernsteinPolyCastel[0][0][t] = 1
                elseif kk == 0 then
                    __bernsteinPolyCastel[mm][0][t] = (1-t) * __bernsteinPolyCastel[mm-1][0][t]
                elseif kk == mm then
                    __bernsteinPolyCastel[mm][mm][t] = t * __bernsteinPolyCastel[mm-1][mm-1][t]
                else
                    __bernsteinPolyCastel[mm][kk][t] = (1-t) * __bernsteinPolyCastel[mm-1][kk][t] + t * __bernsteinPolyCastel[mm-1][kk-1][t]
                end
                count = count + 1
            end
        end
    end
    return __bernsteinPolyCastel[m][k][t]
end

bezierPlane = function (initPlane, posX, posY)
    local sizeX, sizeY = #initPlane[1]-1, #initPlane-1
    local v = 0
    for k1 = 0, sizeY do
        for k2 = 0, sizeX do
            v = v + bernsteinPolyCasteljau(k1, sizeY, posY/sizeY) * bernsteinPolyCasteljau(k2, sizeX, posX/sizeX) * initPlane[k1+1][k2+1]
        end
    end
    return v
end

if debug.getinfo(1).short_src == arg[0] then
    if #arg ~= 4 then exit("Expected 4 arguments, but got " .. tostring(#arg) .. ".")
    elseif not arg[1]:match("^%d+$") or tonumber(arg[1]) == 0 then exit("First argument must be a positiv integer.")
    elseif not list.all({arg[3], arg[4]}, function (s) return (s:match("^%d+$") or s:match("^%d+%.%d+$")) and tonumber(s) < tonumber(arg[1]) end) then
        exit(("Coordinates must be numbers between 0 and %d include, but got '%s' and '%s'."):format(tonumber(arg[1])-1, arg[3], arg[4]))
    end

    local size, posX, posY = tonumber(arg[1]), tonumber(arg[3]), tonumber(arg[4])
    local data = list.generate(size, function() return list.generate(size, function() return 0 end) end)

    local file, err = io.open(arg[2])
    if err then exit(("Failed to open '%s': %s."):format(arg[2], err)) end
    for l in file:lines() do
        local x, y, p = l:match("^(%d+);(%d+);(.+)$")
        if not p or not (p:match("^%d+$") or p:match("^%d+.%d+$")) then
            exit("Expected format '\\d+;\\d+;\\d+(.\\d+)?', but got '"..l.."'.")
        elseif tonumber(x) > size-1 or tonumber(y) > size-1 or tonumber(p) > 100 then
            exit(("Invalid input: Coordinates must be between 0 and %d and pollution level between 0 and 100, but got: x:%s,y:%s,p:%s."):format(size-1, x, y, p))
        end
        data[tonumber(y)+1][tonumber(x)+1] = tonumber(p) / 100
    end

    --for y = size-1, 0, -0.2 do
    --    for x = 0, size-1, 0.2 do
    --        io.write(("%0.2f\t"):format(bezierPlane(data, x, y)))
    --    end
    --    print()
    --end

    print(("%.02f"):format(bezierPlane(data, posX, posY)*100))
end