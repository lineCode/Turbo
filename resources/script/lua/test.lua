--local foo = Foo.new("fred")
--local m = foo:add(3, 4)
--
--print(m)

--LuaPoint.x = 2

local asd = LuaPoint.new(2, 3)



for k,v in pairs(getmetatable(asd)) do
    print(k, type(v))
end