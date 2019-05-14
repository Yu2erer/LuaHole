//
// Created by yu2erer on 2019/5/10.
//

#ifndef LUAHOLE_LUAHOLEPOP_H
#define LUAHOLE_LUAHOLEPOP_H
#include "LuaHeader.h"

namespace LuaHole {

    template <typename T>
    inline T __popValue(lua_State *L, int index = -1) {
        // TODO: 暂时还不知道这里可能会用在哪里...
        return 0;
    }

    template <>
    inline int __popValue(lua_State *L, int index) {
        int ret = static_cast<int>(lua_tonumber(L, index));
        index == -1 ? lua_pop(L, 1) : lua_remove(L, index);
        return ret;
    }

    template <>
    inline double __popValue(lua_State *L, int index) {
        double ret = static_cast<double>(lua_tonumber(L, index));
        index == -1 ? lua_pop(L, 1) : lua_remove(L, index);
        return ret;
    }

    template <>
    inline float __popValue(lua_State *L, int index) {
        float ret = static_cast<float>(lua_tonumber(L, index));
        index == -1 ? lua_pop(L, 1) : lua_remove(L, index);
        return ret;
    }

    template <>
    inline std::string __popValue(lua_State *L, int index) {
        std::string ret = static_cast<std::string>(lua_tostring(L, index));
        index == -1 ? lua_pop(L, 1) : lua_remove(L, index);
        return ret;
    }

    template <>
    inline const char* __popValue(lua_State *L, int index) {
        const char* ret = lua_tostring(L, index);
        index == -1 ? lua_pop(L, 1) : lua_remove(L, index);
        return ret;
    }

    template <>
    inline bool __popValue(lua_State *L, int index) {
        bool ret = lua_toboolean(L, index) == 1;
        index == -1 ? lua_pop(L, 1) : lua_remove(L, index);
        return ret;
    }

    // 获取 Lua 全局变量
    template <typename T>
    inline T Get(lua_State *L, const char *name) {
        lua_getglobal(L, name);
        return __popValue<T>(L);
    }

    template <typename T>
    inline T Get(lua_State *L, int index) {
        return __popValue<T>(L, index);
    }
}

#endif //LUAHOLE_LUAHOLEPOP_H
