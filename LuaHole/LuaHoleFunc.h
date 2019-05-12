//
// Created by yu2erer on 2019-05-12.
//

#ifndef LUAHOLE_LUAHOLEFUNC_H
#define LUAHOLE_LUAHOLEFUNC_H
#include "LuaHeader.h"

namespace LuaHole {

#ifndef PUSH_FUNC
#define PUSH_FUNC do{\
lua_pushlightuserdata(L, (void*)func);\
lua_pushcclosure(L, proxyFunc, 1);\
lua_setglobal(L, name);\
}while(0)
#endif

    template <typename FUNC>
    class funcBind{};

    template <typename Ret>
    class funcBind<Ret(*)()> {
    public:
        static void pushFunc(lua_State *L, const char *name, Ret(*func)()) {
            PUSH_FUNC;
        }
        static int proxyFunc(lua_State *L) {
            ((func)lua_touserdata(L, lua_upvalueindex(1)))();
            return 0;
        }
    private:
        typedef Ret(*func)();
    };

    template <typename FUNC>
    void RegisterFunc(lua_State *L, const char *name, FUNC fn) {
        funcBind<FUNC>::pushFunc(L, name, fn);
    }
}

#endif //LUAHOLE_LUAHOLEFUNC_H
