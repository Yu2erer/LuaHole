#include <iostream>
#include <string>
#include "LuaHole.h"

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
    LuaHole::Set(L, "sbool", false);
    const char *str = "I come from C++";
    LuaHole::Set(L, "sstring", str);
}

int FuncTest(int i, const char *j, float f, bool b) {
    printf("func: %s\n",__func__);
    cout << "FuncTest " << i << " " << j << " " << " " << b << " " << f  << endl;
    return 10;
}

int main() {
    LuaHole::LuaWrapper L;
//    TestSetToLua(L);
    L.RegisterFunc("FuncTest", FuncTest);
//    L.RegisterFunc("printf", printf);
    L.doFile("Test.lua");
//    L.doString("print (\"C++ doString Succ\")");
//    TestGetFromLua(L);


    return 0;
}