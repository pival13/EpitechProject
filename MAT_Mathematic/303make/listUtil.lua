local range = function (i, j, k)
	local z = {}
	for x = i, j or i, k or (i <= j and 1 or -1) do
		z[#z + 1] = x
	end
	return z
end

local generate = function (n, f)
	local z = {}
	for i = 1, n do
		z[i] = f(i)
	end
	return z
end

local array; do
	local select = select
array = function (x, rank, ...)
	local z = {}
	if select('#', ...) == 0 then
		for i = 1, rank do
			z[i] = x
		end
	else
		for i = 1, rank do
			z[i] = array(x, ...)
		end
	end
	return z
end; end



-- Counting

local any = function (t, pr)
	for i = 1, #t do
		if pr(t[i], i) then
			return true
		end
	end
	return false
end

local all = function (t, pr)
	for i = 1, #t do
		if not pr(t[i], i) then
			return false
		end
	end
	return true
end

local none = function (t, pr)
	for i = 1, #t do
		if pr(t[i], i) then
			return false
		end
	end
	return true
end

local count = function (t, x)
	local z = 0
	for i = 1, #t do
		if t[i] == x then
			z = z + 1
		end
	end
	return z
end

local count_if = function (t, pr)
	local z = 0
	for i = 1, #t do
		if pr(t[i], i) then
			z = z + 1
		end
	end
	return z
end



-- Searching

local find = function (t, x, b)
	b = b or 1
	if b < 0 then
		b = b + #t + 1
	end
	for i = b, #t do
		if t[i] == x then
			return i, t[i]
		end
	end
end

local find_if = function (t, pr, b)
	b = b or 1
	if b < 0 then
		b = b + #t + 1
	end
	for i = b, #t do
		if pr(t[i], i) then
			return i, t[i]
		end
	end
end

local rfind = function (t, x, e)
	e = e or #t
	if e < 0 then
		e = e + #t + 1
	end
	for i = e, 1, -1 do
		if t[i] == x then
			return i, t[i]
		end
	end
end

local rfind_if = function (t, pr, e)
	e = e or #t
	if e < 0 then
		e = e + #t + 1
	end
	for i = e, 1, -1 do
		if pr(t[i], i) then
			return i, t[i]
		end
	end
end

local min = function (t, op)
	if #t > 0 then
		local k = 1
		local v = t[k]
		if op then
			for i = 2, #t do
				local v2 = t[i]
				if op(v2, v) then
					k = i
					v = v2
				end
			end
		else
			for i = 2, #t do
				local v2 = t[i]
				if v2 < v then
					k = i
					v = v2
				end
			end
		end
		return k, v
	end
end

local max = function (t, op)
	if #t > 0 then
		local k = 1
		local v = t[k]
		if op then
			for i = 2, #t do
				local v2 = t[i]
				if op(v, v2) then
					k = i
					v = v2
				end
			end
		else
			for i = 2, #t do
				local v2 = t[i]
				if v < v2 then
					k = i
					v = v2
				end
			end
		end
		return k, v
	end
end

local minmax = function (t, op)
	if #t > 0 then
--		local klo = 1
--		local khi = 1
		local vlo = t[1]
		local vhi = t[1]
		if op then
			for i = 2, #t do
				local v2 = t[i]
				if op(vhi, v2) then
--					khi = i
					vhi = v2
				elseif op(v2, vlo) then
--					klo = i
					vlo = v2
				end
			end
		else
			for i = 2, #t do
				local v2 = t[i]
				if vhi < v2 then
--					khi = i
					vhi = v2
				elseif v2 < vlo then
--					klo = i
					vlo = v2
				end
			end
		end
		return vlo, vhi
	end
end



-- Comparison

local equal = function (t1, t2)
	if #t1 == #t2 then
		for i = 1, #t1 do
			if t1[i] ~= t2[i] then
				return false
			end
		end
		return true
	end
	return false
end

local compare; do
	local mathmin = math.min
compare = function (t1, t2)
	for i = 1, mathmin(#t1, #t2) do
		local a, b = t1[i], t2[i]
		if a < b then
			return -1
		elseif a > b then
			return 1
		end
	end
	return #t1 < #t2 and -1 or #t1 > #t2 and 1 or 0
end end

local equality_mixin = function ()
	return {__eq = equal}
end

local ordering_mixin = function ()
	return {
		__eq = equal,
		__lt = function (x, y) return compare(x, y) < 0 end,
		__le = function (x, y) return compare(x, y) <= 0 end,
	}
end


-- Selection

local sub = function (t, i, j)
	j = j or #t
	if i < 0 then
		i = i + #t + 1
	end
	if j < 0 then
		j = j + #t + 1
	end
	local z = {}
	for k = i, j do
		z[#z + 1] = t[k]
	end
	return z
end

local select = function (t, pr)
	local z = {}
	for i = 1, #t do
		if pr(t[i], i) then
			z[#z + 1] = t[i]
		end
	end
	return z
end

local keep_if = function (t, pr)
	local j = 1
	for i = 1, #t do
		if pr(t[i], i) then
			t[j] = t[i]
			j = j + 1
		end
	end
	for i = #t, j, -1 do
		t[i] = nil
	end
	return t
end

local delete_if = function (t, pr)
	local j = 1
	local z = {}
	for i = 1, #t do
		local v = t[i]
		if pr(v, i) then
			z[#z + 1] = v
		else
			t[j] = v
			j = j + 1
		end
	end
	for i = #t, j, -1 do
		t[i] = nil
	end
	return z
end

local uniq = function (t, f)
	local z = {}
	local set = {}
	if f ~= nil then
		for i = 1, #t do
			local v = t[i]
			local fv = f(v)
			if not set[fv] then
				set[fv] = true
				z[#z + 1] = v
			end
		end
	else
		for i = 1, #t do
			local v = t[i]
			if not set[v] then
				set[v] = true
				z[#z + 1] = v
			end
		end
	end
	return z
end

local compact; do
	local pairs, type, tablesort = pairs, type, table.sort
compact = function (t)
	local z = {}
	local ks = {}
	for k in pairs(t) do
		if type(k) == 'number' then
			ks[#ks + 1] = k
		end
	end
	tablesort(ks)
	for i = 1, #ks do
		z[#z + 1] = t[ks[i]]
	end
	return z
end end



-- Transformation

local reverse = function (t)
	local z = {}
	for i = #t, 1, -1 do
		z[#z + 1] = t[i]
	end
	return z
end

local reverse_self = function (t)
	for i = 1, #t / 2 do
		local j = #t + 1 - i
		t[i], t[j] = t[j], t[i]
	end
	return t
end

local map = function (t, f)
	local z = {}
	for i = 1, #t do
		z[i] = f(t[i], i)
	end
	return z
end

local map_self = function (t, f)
	for i = 1, #t do
		t[i] = f(t[i], i)
	end
	return t
end

local zip = function (t1, t2, op)
	local z = {}
	for i = 1, #t1 do
		z[i] = op(t1[i], t2[i])
	end
	return z
end

local sort_by; do
	local tablesort = table.sort
sort_by = function (t, f)
	local y = map(t, f)
	local indices = range(1, #t)
	tablesort(indices, function (i, j) return y[i] < y[j] end)
	map_self(indices, function (i) return t[i] end)
	return indices
end end

local concat = function (t1, t2)
	local z = {}
	for i = 1, #t1 do
		z[i] = t1[i]
	end
	for i = 1, #t2 do
		z[#z + 1] = t2[i]
	end
	return z
end

local concat_self = function (t1, t2)
	for i = 1, #t2 do
		t1[#t1 + 1] = t2[i]
	end
	return t1
end

local to_set = function (t)
	local z = {}
	for i = 1, #t do
		z[t[i]] = true
	end
	return z
end

local transpose = function (t)
	local maxsize = 0
	for i = 1, #t do
		local s = #t[i]
		if s > maxsize then
			maxsize = s
		end
	end
	local z = {}
	for i = 1, maxsize do
		z[#z + 1] = {}
	end
	for i = 1, #t do
		local v = t[i]
		for j = 1, #v do
			z[j][i] = v[j]
		end
	end
	return z
end



-- Other

local reduce = function (t, op, z)
	if z ~= nil then
		for i = 1, #t do
			z = op(z, t[i])
		end
	else
		z = t[1]
		for i = 2, #t do
			z = op(z, t[i])
		end
	end
	return z
end

local sum = function (t)
	local z = 0
	for i = 1, #t do
		z = z + t[i]
	end
	return z
end

local group_by = function (t, f)
	local z = {}
	for i = 1, #t do
		local v = t[i]
		local k = f(v, i)
		if not z[k] then
			z[k] = {}
		end
		z[k][#z[k] + 1] = v
	end
	return z
end


return {
	range = range,
	generate = generate,
	array = array,

	any = any,
	all = all,
	none = none,
	count = count,
	count_if = count_if,

	find = find,
	find_if = find_if,
	rfind = rfind,
	rfind_if = rfind_if,
	min = min,
	max = max,
	minmax = minmax,

	equal = equal,
	compare = compare,
	equality_mixin = equality_mixin,
	ordering_mixin = ordering_mixin,

	sub = sub,
	select = select,
	keep_if = keep_if,
	delete_if = delete_if,
	uniq = uniq,
	compact = compact,

	reverse = reverse,
	reverse_self = reverse_self,
	map = map,
	map_self = map_self,
	zip = zip,
	sort_by = sort_by,
	concat = concat,
	concat_self = concat_self,
	to_set = to_set,
	transpose = transpose,

	reduce = reduce,
	sum = sum,
	group_by = group_by,
}