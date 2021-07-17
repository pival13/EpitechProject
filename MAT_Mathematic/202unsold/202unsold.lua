#! /bin/lua

local unsold = function (a, b)
    if not a or not b or a < 50 or b < 50 then os.exit(84) end
    local tbl = {}

    print(string.rep("-", 80))
    
    print("", "X=10", "X=20", "X=30", "X=40", "X=50", "Y law")
    for y = 10, 50, 10 do
        tbl[y] = {}
        tbl[y]["s"] = 0
        io.write(string.format( "Y=%d",y))
        for x = 10, 50, 10 do
            tbl[y][x] = (a-x)*(b-y)/(5*a-150)/(5*b-150)
            tbl[y].s = tbl[y].s + tbl[y][x]
            io.write(string.format("\t%0.03f",tbl[y][x]))
        end
        io.write(string.format("\t%0.03f\n", tbl[y].s))
    end
    io.write("X law")
    tbl["s"] = {}
    tbl.s["s"] = 0
    for x = 10, 50, 10 do
        tbl.s[x] = 0
        for y = 10, 50, 10 do tbl.s[x] = tbl.s[x] + tbl[y][x] end
        tbl.s.s = tbl.s.s + tbl.s[x]
        io.write(string.format("\t%0.03f", tbl.s[x]))
    end
    io.write(string.format("\t%0.03f\n", tbl.s.s))

    print(string.rep("-", 80))

    tbl["z"] = {}
    io.write("z")
    for z = 20, 100, 10 do io.write(string.format("\t%d",z)) end
    io.write("\np(Z=z)")
    for z = 20, 100, 10 do
        tbl.z[z] = 0
        for x = 10, z-10, 10 do
            if x <= 50 then
                local y = z-x
                if y >= 10 and y <= 50 then
                    tbl.z[z] = tbl.z[z] + tbl[y][x]
                end
            end
        end
        io.write(string.format( "\t%0.03f",tbl.z[z]))
    end

    print("\n"..string.rep("-", 80))

    local s = 0
    local v = 0
    for i, j in pairs(tbl.s) do if tonumber(i) then
        s = s + tonumber(i)*j
        v = v + tonumber(i)*tonumber(i)*j
    end end
    print(string.format("expected value of X:\t%.01f",s))
    print(string.format("variance of X:\t\t%.01f",v-s*s))
    s = 0
    v = 0
    for i, j in pairs(tbl) do if tonumber(i) then
        s = s + tonumber(i)*j.s
        v = v + tonumber(i)*tonumber(i)*j.s
    end end
    print(string.format("expected value of Y:\t%.01f",s))
    print(string.format("variance of Y:\t\t%.01f",v-s*s))
    s = 0
    v = 0
    for i, j in pairs(tbl.z) do if tonumber(i) then
        s = s + tonumber(i)*j
        v = v + tonumber(i)*tonumber(i)*j
    end end
    print(string.format("expected value of Z:\t%.01f",s))
    print(string.format("variance of Z:\t\t%.01f",v-s*s))

    print(string.rep("-", 80))
end

local main = function (arg)
    if #arg ~= 2 then os.exit(84) end
    unsold(tonumber(arg[1]),tonumber(arg[2]))
    return 0
end

return main(arg)