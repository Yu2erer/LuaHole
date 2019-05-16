//
// Created by yu2erer on 2019/5/10.
//

#ifndef LUAHOLE_LUAHOLE_H
#define LUAHOLE_LUAHOLE_H
#include "LuaHeader.h"
#include "LuaHolePop.h"
#include "LuaHolePush.h"
#include "LuaHoleFunc.h"
#include "LuaHoleHelper.h"
#include "LuaHoleClass.h"

namespace LuaHole {

    class LuaWrapper {
    public:
        operator lua_State* () const { return L; }

        bool doFile(const char *filename) const {
            if (!L) { return false; }
            if (luaL_dofile(L, filename)) {
                const char *err = lua_tostring(L, -1);
                lua_pop(L, 1);
                DEBUG(err);
                return false;
            }
            return true;
        }
        bool doString(const char *str) const {
            if (!L) { return false; }
            if (luaL_dostring(L, str)) {
                const char *err = lua_tostring(L, -1);
                lua_pop(L, 1);
                DEBUG(err);
                return false;
            }
            return true;
        }
        LuaWrapper() {
            L = luaL_newstate();
            luaL_openlibs(L);
        }
        ~LuaWrapper() {
            if (L) { lua_close(L); }
            L = nullptr;
        }

        template <typename T>
        T Get(const char *name) const { return LuaHole::Get<T>(L, name); }
        template <typename T>
        void Set(const char *name, const T &arg) const { LuaHole::Set(L, name, arg); }
        template <typename FUNC>
        void RegFunc(const char *name, FUNC fn) const { LuaHole::RegFunc(L, name, fn); }
    private:
        lua_State *L;
    };

}
#endif //LUAHOLE_LUAHOLE_H
