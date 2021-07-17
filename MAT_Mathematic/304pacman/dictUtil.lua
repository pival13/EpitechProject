local pairs = pairs

local from_lists = function (ks, vs)
	local z = {}
	for i = 1, #ks do
		z[ks[i]] = vs[i]
	end
	return z
end

local from_ipairs = function (s, g)
	local z = {}
	for i = 1, #s do
		local k, v = g(s[i], i)
		if k ~= nil then
			z[k] = v
		end
	end
	return z
end

local from_pairs = function (t, g)
	local z = {}
	for k, v in pairs(t) do
		local k2, v2 = g(v, k)
		if k2 ~= nil then
			z[k2] = v2
		end
	end
	return z
end

local generate = function (s, g)
	local z = {}
	for i = 1, #s do
		z[s[i]] = g(s[i], i)
	end
	return z
end

local size = function (t)
	local z = 0
	for _ in pairs(t) do
		z = z + 1
	end
	return z
end

local any = function (t, pr)
	for k, v in pairs(t) do
		if pr(v, k) then
			return true
		end
	end
	return false
end

local all = function (t, pr)
	for k, v in pairs(t) do
		if not pr(v, k) then
			return false
		end
	end
	return true
end

local none = function (t, pr)
	for k, v in pairs(t) do
		if pr(v, k) then
			return false
		end
	end
	return true
end

local count = function (t, x)
	local z = 0
	for _, v in pairs(t) do
		if v == x then
			z = z + 1
		end
	end
	return z
end

local count_if = function (t, pr)
	local z = 0
	for k, v in pairs(t) do
		if pr(v, k) then
			z = z + 1
		end
	end
	return z
end

local find = function (t, x)
	for k, v in pairs(t) do
		if v == x then
			return k, v
		end
	end
end

local find_if = function (t, pr)
	for k, v in pairs(t) do
		if pr(v, k) then
			return k, v
		end
	end
end

local clone = function (t)
	local z = {}
	for k, v in pairs(t) do
		z[k] = v
	end
	return z
end

local map = function (t, f)
	local z = {}
	for k, v in pairs(t) do
		z[k] = f(v, k)
	end
	return z
end

local map_self = function (t, f)
	for k, v in pairs(t) do
		t[k] = f(v, k)
	end
	return t
end

local zip = function (t1, t2, op)
	local z = {}
	for k, v in pairs(t1) do
		z[k] = op(v, t2[k])
	end
	return z
end

local select = function (t, pr)
	local z = {}
	for k, v in pairs(t) do
		if pr(v, k) then
			z[k] = v
		end
	end
	return z
end

local merge_self = function (t1, t2, g)
	if g then
		for k, v in pairs(t2) do
			if t1[k] ~= nil then
				t1[k] = g(t1[k], v, k)
			else
				t1[k] = v
			end
		end
	else
		for k, v in pairs(t2) do
			t1[k] = v
		end
	end
	return t1
end

local merge = function (t1, t2, g)
	return merge_self(clone(t1), t2, g)
end

local invert = function (t)
	local z = {}
	for k, v in pairs(t) do
		z[v] = k
	end
	return z
end

local keys = function (t)
	local z = {}
	for k in pairs(t) do
		z[#z + 1] = k
	end
	return z
end

local values = function (t)
	local z = {}
	for _, v in pairs(t) do
		z[#z + 1] = v
	end
	return z
end

local to_lists = function (t)
	local ks = {}
	local vs = {}
	for k, v in pairs(t) do
		ks[#ks + 1] = k
		vs[#vs + 1] = v
	end
	return ks, vs
end

local transpose = function (t)
	local z = {}
	for k1, v1 in pairs(t) do
		for k2, v2 in pairs(v1) do
			z[k2] = z[k2] or {}
			z[k2][k1] = v2
		end
	end
	return z
end

local remove = function (t, k)
	local z = t[k]
	t[k] = nil
	return z
end

local sorted_pairs = function (t, f)
	local ks = keys(t)
	if f then
		table.sort(ks, function (k1, k2)
			return f(t[k1], t[k2], k1, k2)
		end)
	else
		table.sort(ks)
	end
	local i = 0
	return function ()
		i = i + 1
		if i <= #ks then
			return ks[i], t[ks[i]]
		end
	end
end

return {
	from_lists = from_lists,
	from_ipairs = from_ipairs,
	from_pairs = from_pairs,
	generate = generate,

	size = size,
	any = any,
	all = all,
	none = none,
	count = count,
	count_if = count_if,

	find = find,
	find_if = find_if,

	clone = clone,
	map = map,
	map_self = map_self,
	zip = zip,
	select = select,
	merge = merge,
	merge_self = merge_self,
	invert = invert,
	keys = keys,
	values = values,
	to_lists = to_lists,
	transpose = transpose,

	remove = remove,
	sorted_pairs = sorted_pairs,
}