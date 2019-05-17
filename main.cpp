#include <iostream>
#include <string>
#include "LuaHole.h"
#include "Student.h"

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
    cout << "FuncTest " << i << " " << j << " " << " " << b << " " << f  << endl;
    return 10;
}

int main() {
    LuaHole::LuaWrapper L;
//    TestSetToLua(L);
//    L.RegFunc("FuncTest", FuncTest);
//    L.RegFunc("printf", printf);
    LuaHole::RegClass<Student>(L, "ss", LuaHole::constructor<Student>);
    LuaHole::RegMethod(L, "print", &Student::print);


    L.doFile("Test.lua");
    string i = LuaHole::Call<string>(L, "luafunc", 38);
//    cout << i << endl;
//    L.doString("print (\"C++ doString Succ\")");
//    TestGetFromLua(L);
//    LuaHole::RegMethod(L, "getAge", &Student::getAge);
    return 0;
}