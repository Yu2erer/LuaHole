//
// Created by yu2erer on 2019/5/16.
//

#ifndef LUAHOLE_LUAHOLEUSERDATA_H
#define LUAHOLE_LUAHOLEUSERDATA_H
#include "LuaHeader.h"

namespace LuaHole {

    template <typename T>
    struct UserData {
        UserData(T *obj, bool useLuaGC = true) : obj(obj), useLuaGC(useLuaGC) { }
        ~UserData() { if (useLuaGC) { delete obj; } }
        T *obj;
        bool useLuaGC;
    };
}

#endif //LUAHOLE_LUAHOLEUSERDATA_H
