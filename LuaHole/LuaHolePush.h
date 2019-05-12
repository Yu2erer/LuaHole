//
// Created by yu2erer on 2019/5/10.
//

#ifndef LUAHOLE_LUAHOLEPUSH_H
#define LUAHOLE_LUAHOLEPUSH_H
#include "LuaHeader.h"

namespace LuaHole {

    template <typename T>
    class objPush {
    public:
        objPush(lua_State *L, const T &arg) {
            if (lua_Number(arg) == lua_Integer(arg)) {
                lua_pushinteger(L, lua_Integer(arg));
            } else {
                lua_pushnumber(L, lua_Number(arg));
            }
        }
    };

    template <>
    class objPush<const char *> {
    public:
        objPush(lua_State *L, const char *arg) {
            lua_pushstring(L, arg);
        }
    };

    template <>
    class objPush<char *> {
    public:
        objPush(lua_State *L, char *arg) {
            lua_pushstring(L, arg);
        }
    };

    template <>
    class objPush<std::string> {
    public:
        objPush(lua_State *L, std::string &arg) {
            lua_pushlstring(L, arg.c_str(), arg.size());
        }
    };

    template <>
    class objPush<bool> {
    public:
        objPush(lua_State *L, bool arg) {
            lua_pushboolean(L,arg);
        }
    };

    // Set lua global variable
    template <typename T>
    inline void Set(lua_State *L, const char *name, const T &arg) {
        objPush<T>(L, arg);
        lua_setglobal(L, name);
    }
}

#endif //LUAHOLE_LUAHOLEPUSH_H
