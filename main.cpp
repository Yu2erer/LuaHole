#include <iostream>
#include <string>
#include "LuaHole.h"
#include "LuaHolePop.h"
#include "LuaHolePush.h"

using namespace std;

void TestGetFromLua(LuaHole::LuaWrapper &L) {
    cout << "string Test: " << endl;
    cout << L.Get<string>("strTest") << endl;

    cout << "int Test: " << endl;
    cout << LuaHole::Get<int>(L, "iTest") << endl;

    cout << "float Test: " << endl;
    cout << L.Get<float>("fTest") << endl;

    cout << "double Test: " << endl;
    cout << LuaHole::Get<double>(L, "dTest") << endl;

    cout << "bool Test: " << endl;
    cout << L.Get<bool>("bTest") << endl;
}

void TestSetToLua(LuaHole::LuaWrapper &L) {
    L.Set("sint", 520);
    LuaHole::Set(L, "sdouble", 122.57);
}

int main() {
    LuaHole::LuaWrapper L;
    TestSetToLua(L);
    L.doFile("Test.lua");
    L.doString("print (\"C++ doString Succ\")");
    TestGetFromLua(L);



    return 0;
}