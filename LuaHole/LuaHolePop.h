//
// Created by yu2erer on 2019/5/10.
//

#ifndef LUAHOLE_LUAHOLEPOP_H
#define LUAHOLE_LUAHOLEPOP_H
#include "LuaHeader.h"

namespace LuaHole {

    template <typename T>
    inline T __popValue(lua_State *L, int index = -1, bool pop = true) {
        // TODO: 暂时还不知道这里可能会用在哪里...
        return 0;
    }

    template <>
    inline int __popValue(lua_State *L, int index, bool pop) {
        int ret = static_cast<int>(lua_tonumber(L, index));
        pop ? lua_pop(L, 1) : ((void)0);
        return ret;
    }

    template <>
    inline double __popValue(lua_State *L, int index, bool pop) {
        double ret = static_cast<double>(lua_tonumber(L, index));
        pop ? lua_pop(L, 1) : ((void)0);
        return ret;
    }

    template <>
    inline float __popValue(lua_State *L, int index, bool pop) {
        float ret = static_cast<float>(lua_tonumber(L, index));
        pop ? lua_pop(L, 1) : ((void)0);
        return ret;
    }

    template <>
    inline std::string __popValue(lua_State *L, int index, bool pop) {
        std::string ret = static_cast<std::string>(lua_tostring(L, index));
        pop ? lua_pop(L, 1) : ((void)0);
        return ret;
    }

    template <>
    inline const char* __popValue(lua_State *L, int index, bool pop) {
        const char* ret = lua_tostring(L, index);
        pop ? lua_pop(L, 1) : ((void)0);
        return ret;
    }

    template <>
    inline bool __popValue(lua_State *L, int index, bool pop) {
        bool ret = lua_toboolean(L, index) == 1;
        pop ? lua_pop(L, 1) : ((void)0);
        return ret;
    }

    // 获取 Lua 全局变量
    template <typename T>
    inline T Get(lua_State *L, const char *name) {
        lua_getglobal(L, name);
        return __popValue<T>(L, true);
    }

    template <typename T>
    inline T Get(lua_State *L, int index) {
        return __popValue<T>(L, index, false);
    }
}

#endif //LUAHOLE_LUAHOLEPOP_H
