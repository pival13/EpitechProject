#!/usr/bin/env lua

local List = require 'listUtil'
local Dict = require 'dictUtil'
local Util = require 'util'

local parseFile = function (content)
    if not content or #content == 0 then os.exit(84) end
    
    elem = {}
    local size = #Dict.keys(elem)
    content:gsub("[^\n]*", function (s)
        if s == "" then return end
        s:gsub("^(.-);.-;(%d+)(.*)$", function (id, time, other)
            if elem[id] then print("Duplicate id: " .. id); os.exit(84) end
            elem[id] = {
                time = time,
                deps = {},
                check = false
            }
            other:gsub(";([^;]*)", function (dep)
                if dep == id then print("A prerequisite is the task itself: " .. dep); os.exit(84) end
                table.insert(elem[id]["deps"], dep)
            end)
        end)
        if #Dict.keys(elem) == size then print("Wrongly formatted line"); os.exit(84)
        else size = size + 1
        end
    end)
    if #Dict.keys(elem) == 0 then print("Empty file"); os.exit(84) end
    
    local ids = Dict.keys(elem)
    for _, e in ipairs(ids) do
        if List.any(elem[e]["deps"], function (dep) return List.count(ids, dep) ~= 1 end) then
            print("Unknow prerequisite for " .. e)
            os.exit(84)
        end
    end
    return elem
end

local getMinTime; getMinTime = function (elem, elemId)
    if elem[elemId]["tmin"] then return end
    if elem[elemId].check then print("Unexpected loop"); os.exit(84) end
    elem[elemId].check = true
    
    local deps = elem[elemId]["deps"]
    if #deps == 0 then
        elem[elemId]["tmin"] = 0
    else
        local times = {}
        for _, d in ipairs(deps) do
            getMinTime(elem, d)
            table.insert(times, elem[d]["tmin"] + elem[d].time)
        end
        _, elem[elemId].tmin = List.max(times)
    end
end

local getMaxTime; getMaxTime = function (elem, elemId, maxTime)
    if elem[elemId]["tmax"] then return end

    local ids = Dict.keys(elem)
    local deps = Dict.values(List.generate(#ids, function (i) return List.find(elem[ids[i]].deps, elemId) and ids[i] or nil end))
    if #deps == 0 then
        elem[elemId].tmax = maxTime - elem[elemId].time
    else
        local times = {}
        for _, d in ipairs(deps) do
            getMaxTime(elem, d, maxTime)
            table.insert(times, elem[d].tmax - elem[elemId].time)
        end
        _, elem[elemId].tmax = List.min(times)
    end
end

local getTimes = function (elems)
    for elemId, elem in pairs(elems) do
        getMinTime(elems, elemId)
    end
    
    local ids = Dict.keys(elems)
    local _, maxTime = List.max(List.generate(#ids, function (i) return elems[ids[i]].tmin + elems[ids[i]].time end))
    for elemId, elem in pairs(elems) do
        getMaxTime(elems, elemId, maxTime)
    end
end

if debug.getinfo( 1, 'S' ).short_src == arg[0] then
    if #arg ~= 1 then print("Expected one argument"); os.exit(84) end

    local elem = parseFile(Util.readFile(arg[1]))

    getTimes(elem)

    local ids = Dict.keys(elem)
    table.sort(ids, function (v1, v2)
        if elem[v1].tmin < elem[v2].tmin then return true
        elseif elem[v1].tmin > elem[v2].tmin then return false
        else
            if elem[v1].time < elem[v2].time then return true
            elseif elem[v1].time > elem[v2].time then return false
            else
                return v1 < v2
            end
        end
    end)
    local _, maxTime = List.max(List.generate(#ids, function (i) return elem[ids[i]].tmin + elem[ids[i]].time end))

    print(("Total duration of construction: %d weeks"):format(maxTime))
    print()
    for _, elemId in ipairs(ids) do
        if elem[elemId].tmin == elem[elemId].tmax then
            print(("%s must begin at t=%d"):format(elemId, elem[elemId].tmin))
        else
            print(("%s must begin between t=%d and t=%d"):format(elemId, elem[elemId].tmin, elem[elemId].tmax))
        end
    end
    print()
    for _, elemId in ipairs(ids) do
        io.write(("%s\t(%d)\t"):format(elemId, elem[elemId].tmax - elem[elemId].tmin))
        for i = 1, elem[elemId].tmin do io.write(" ") end
        for i = 1, elem[elemId].time do io.write("=") end
        print()
    end
end
