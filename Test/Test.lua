 --TestGetFromLua
strTest = "Hello World"
iTest = 123
fTest = 1.2
dTest = 3.14159
bTest = true
--
-- TestSetFromC++
--print(sint)
--print(sdouble)
--print(sbool)
--print(sstring)

--t = FuncTest(3, "hahahanihao!", 3.14, true)
--print(t)
--luafunc = 3
function luafunc(i)
    print("LuaFunc say Hello")
    return i.." haha"
end

 local s = ss(520)
 s:print()
 s:setAge(300)