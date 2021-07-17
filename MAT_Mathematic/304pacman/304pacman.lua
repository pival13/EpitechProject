#! /usr/bin/env lua

local List = require 'listUtil'
local Dict = require 'dictUtil'

local printMap = function (map, charSpace, charWall)
    io.write(List.reduce(map, function (s, line)
        return s .. List.reduce(line, function (ss, c) return ss .. (c == ' ' and charSpace or (c == '*' and charWall or c)) end, '') .. '\n'
    end, ''))
end

local updateMap = function (map)
    local pos = {}
    List.any(map, function(line, lN)
        local i = List.find(line, 'F')
        if i then table.insert(pos, {lN, i}); return true end
    end)
    while #pos > 0 do
        local nLine, nCol = pos[1][1], pos[1][2]
        if nLine ~= 1 and map[nLine-1][nCol] == 'P' then
            return
        elseif nLine ~= 1 and map[nLine-1][nCol] == ' ' then
            map[nLine-1][nCol] = tostring(((tonumber(map[nLine][nCol]) or 0) + 1) % 10)
            table.insert(pos, {nLine-1, nCol})
        elseif nCol ~= #map[nLine] and map[nLine][nCol+1] == 'P' then
            return
        elseif nCol ~= #map[nLine] and map[nLine][nCol+1] == ' ' then
            map[nLine][nCol+1] = tostring(((tonumber(map[nLine][nCol]) or 0) + 1) % 10)
            table.insert(pos, {nLine, nCol+1})
        elseif nLine ~= #map and map[nLine+1][nCol] == 'P' then
            return
        elseif nLine ~= #map and map[nLine+1][nCol] == ' ' then
            map[nLine+1][nCol] = tostring(((tonumber(map[nLine][nCol]) or 0) + 1) % 10)
            table.insert(pos, {nLine+1, nCol})
        elseif nCol ~= 1 and map[nLine][nCol-1] == 'P' then
            return
        elseif nCol ~= 1 and map[nLine][nCol-1] == ' ' then
            map[nLine][nCol-1] = tostring(((tonumber(map[nLine][nCol]) or 0) + 1) % 10)
            table.insert(pos, {nLine, nCol-1})
        else
            table.remove(pos, 1)
        end
    end
end

if debug.getinfo( 1, 'S' ).short_src == arg[0] then
    if #arg ~= 3 or #arg[2] ~= 1 or #arg[3] ~= 1 then os.exit(84) end

    local f = io.open(arg[1], 'r')
    if not f then os.exit(84) end
    local content = f:read("*all")
    if #content == 0 then os.exit(84) end
    local tbl = {}

    content:gsub("[^\n]+", function (l)
        tbl2 = {}
        l:gsub("[01FP]", function (c) table.insert(tbl2, c == '0' and ' ' or (c == '1' and '*' or c)) end)
        if #tbl2 ~= #l then print("Forbidden characters found"); os.exit(84) end
        table.insert(tbl, tbl2)
    end)
    if #tbl == 0 or List.any(tbl, function(tbl2) return #tbl2 ~= #tbl[1] end) then print("Each lines must have the same size"); os.exit(84) end
    if List.count_if(tbl, function(line) return List.count(line, 'P') == 1 end) ~= 1 or
        List.count_if(tbl, function(line) return List.count(line, 'F') == 1 end) ~= 1 then
            print("Expected 1 'P' (player) and 1 'F' (ghost)")
            os.exit(84)
    end

    updateMap(tbl)
    printMap(tbl, arg[3], arg[2])
end