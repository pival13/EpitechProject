#! /usr/bin/env lua

local list = require 'listUtil'
local exit = require 'util'.failure

local matrix = {
    {4, 1, 0},
    {1, 4, 1},
    {0, 1, 4}
}
local inverse = {
    {15/56, -1/14, 1/56},
    {-1/14, 2/7, -1/14},
    {1/56, -1/14, 15/56}
}

if debug.getinfo(1).short_src == arg[0] then
    if #arg ~= 6 then exit("Expected 6 arguments, but got " .. tostring(#arg))
    elseif not list.all(list.sub(arg, 1, -2), function (s) return (s:match("^%d+$") or s:match("^%d+%.%d+$")) and tonumber(s) > 0 end) or not arg[6]:match("^%d+$") then
        exit("Expected all arguments to be non-null numbers")
    elseif tonumber(arg[6]) < 2 then exit("Expected to display at least 2 points") end

    local rads = list.generate(5, function (i) return tonumber(arg[i]) end)
    local nbInterv = tonumber(arg[6])
    local interv = 20 / (nbInterv - 1)

    local growthRate = list.generate(3, function (i) return 6 * (rads[i+2]-2*rads[i+1]+rads[i]) / 25 end)
    local derivSeconds = list.generate(5, function (i) return i ~= 1 and i ~= 5 and inverse[i-1][1] * growthRate[1] + inverse[i-1][2] * growthRate[2] + inverse[i-1][3] * growthRate[3] or 0 end)

    print(table.pack(("vector result: [%.01f, %.01f, %.01f, %.01f, %.01f]"):format(table.unpack(derivSeconds)):gsub("-0%.0", "0.0"))[1])
    derivSeconds[0] = 0
    derivSeconds[6] = 0
    rads[0] = 0
    rads[6] = 0
    for i = 1, nbInterv do
        local x = (i-1) * interv
        local k = math.floor(x / 5)+1
        local h = 5
        local zi = derivSeconds[k+1]
        local zi1 = derivSeconds[k]
        local xi = k*h
        local xi1 = k*h-h
        local fxi = rads[k+1]
        local fxi1 = rads[k]
        print(("abscissa: %.01f cm\tradius: %.01f cm"):format(x, zi*math.pow(x-xi1, 3)/(6*h) + zi1*math.pow(xi-x, 3)/(6*h) + (fxi/h-zi*h/6)*(x-xi1) + (fxi1/h-zi1*h/6)*(xi-x)))
    end
end
