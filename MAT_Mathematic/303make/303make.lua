#! /usr/bin/env lua

local List = require 'listUtil'
local Dict = require 'dictUtil'

local parseContent = function(content)
    local graph = {}
    local compiled = nil
    content:gsub("[^\n]+", function (l)
        local m, args = l:match("^(.+):%s*(.+)$")
        if m then compiled = m
            if not graph[compiled] then
                graph[compiled] = { ["comm"] = {}, ["dep"] = {} }
            end
            args:gsub("%S+", function (v)
                if graph[v] then
                    table.insert(graph[v]["dep"], compiled)
                else
                    graph[v] = { ["comm"] = {}, ["dep"] = {compiled} }
                end
            end)
        elseif compiled then
            table.insert(graph[compiled]["comm"], l)
        end
    end)
    return graph
end

local drawMatrix = function(graph)
    local keys = Dict.keys(graph)
    table.sort(keys)
    List.map(keys, function (key)
        io.write('[')
        local t = List.map(keys, function (key2) return List.count(List.uniq(graph[key]["dep"]), key2) end)
        io.write(table.concat(t, " "))
        print(']')
    end)
end

local drawCompilation2; drawCompilation2 = function(graph, key, before)
    if #graph[key]["dep"] == 0 then print(before)
    else
        values = Dict.values(graph[key]["dep"])
        table.sort(values)
        List.map(values, function (key2)
            drawCompilation2(graph, key2, before .. ' -> ' .. key2)
        end)
    end
end

local drawCompilation = function(graph)
    local keys = Dict.keys(graph)
    table.sort(keys)
    List.map(keys, function (key)
        if #graph[key]["dep"] ~= 0 then drawCompilation2(graph, key, key) end
    end)
end

local drawCommands = function(graph, comm)
    local deps = graph[comm]["dep"]
    table.sort(deps)

    local comms = {}
    for i=1, #deps do
        local dep = deps[i]
        if graph[dep] then
            local a = graph[dep]["dep"]
            table.sort(a)
            List.concat_self(deps, a)
            deps = List.uniq(deps)
        end
    end
    for _, dep in ipairs(deps) do
        if graph[dep] then
            List.concat_self(comms, graph[dep]["comm"])
        end
    end
    local s = List.reduce(comms, function(s1, s2)
        return s1 .. '\n' .. s2
    end)
    if s then print(s) end
end

if debug.getinfo( 1, 'S' ).short_src == arg[0] then
    if #arg ~= 1 and #arg ~= 2 then os.exit(84) end
    local f = io.open(arg[1], 'r')
    if not f then os.exit(84) end
    local content = f:read("*all")
    if #content == 0 then os.exit(84) end

    local graph = parseContent(content)
    if #Dict.keys(graph) == 0 then os.exit(84) end
    if #arg == 1 then
        drawMatrix(graph)
        print()
        drawCompilation(graph)
    elseif #arg == 2 then
        if not graph[arg[2]] then os.exit(84) end
        drawCommands(graph, arg[2])
    end
end