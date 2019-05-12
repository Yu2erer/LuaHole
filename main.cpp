#include <iostream>
#include <string>
#include "LuaHole.h"
#include "LuaHolePop.h"
#include "LuaHolePush.h"

using namespace std;

void TestGetFromLua(LuaHole::LuaWrapper &L) {
    cout << "string Test: " << L.Get<string>("strTest") << endl;
    cout << "int Test: " << LuaHole::Get<int>(L, "iTest") << endl;
    cout << "float Test: " << L.Get<float>("fTest") << endl;
    cout << "double Test: " << LuaHole::Get<double>(L, "dTest") << endl;
    cout << "bool Test: " << (L.Get<bool>("bTest") == 1 ? "true" : "false") << endl;
}

void TestSetToLua(LuaHole::LuaWrapper &L) {
    L.Set("sint", 520);
    LuaHole::Set(L, "sdouble", 122.57);
    const char *str = "I come from C++";
    LuaHole::Set(L, "sbool", false);
    LuaHole::Set(L, "sstring", str);
}

int main() {
    LuaHole::LuaWrapper L;
    TestSetToLua(L);
    L.doFile("Test.lua");
    L.doString("print (\"C++ doString Succ\")");
    TestGetFromLua(L);



    return 0;
}