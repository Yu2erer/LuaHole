//
// Created by yu2erer on 2019/5/10.
//

#ifndef LUAHOLE_LUAPOPVALUE_H
#define LUAHOLE_LUAPOPVALUE_H
#include "LuaHeader.h"

namespace LuaHole {

    template <typename T>
    inline T popValue(lua_State *L) {
        // TODO: ��ʱ����֪��������ܻ���������...
        return 0;
    }

    template <>
    inline int popValue(lua_State *L) {
        int ret = static_cast<int>(lua_tonumber(L, -1));
        lua_pop(L, 1);
        return ret;
    }

    template <>
    inline double popValue(lua_State *L) {
        double ret = static_cast<double>(lua_tonumber(L, -1));
        lua_pop(L, 1);
        return ret;
    }

    template <>
    inline float popValue(lua_State *L) {
        float ret = static_cast<float>(lua_tonumber(L, -1));
        lua_pop(L, 1);
        return ret;
    }

    template <>
    inline std::string popValue(lua_State *L) {
        std::string ret = static_cast<std::string>(lua_tostring(L, -1));
        lua_pop(L, 1);
        return ret;
    }

    template <>
    inline bool popValue(lua_State *L) {
        bool ret = lua_toboolean(L, -1) == 1;
        lua_pop(L, 1);
        return ret;
    }

    // ��ȡ Lua ȫ�ֱ���
    template <typename T>
    inline T Get(lua_State *L, const char *name) {
        lua_getglobal(L, name);
        return popValue<T>(L);
    }
}

#endif //LUAHOLE_LUAPOPVALUE_H
