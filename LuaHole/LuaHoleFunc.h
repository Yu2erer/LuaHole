//
// Created by yu2erer on 2019-05-12.
//

#ifndef LUAHOLE_LUAHOLEFUNC_H
#define LUAHOLE_LUAHOLEFUNC_H
#include "LuaHeader.h"
#include "LuaHoleTrait.h"
#include "LuaHolePush.h"
#include "LuaHoleTypeList.h"

namespace LuaHole {

#ifndef BIND_CHECK_FUNC_ARG_NUM
#define BIND_CHECK_FUNC_ARG_NUM(_state, _cnt, _ret) do{\
int argsNum = lua_gettop(_state);\
if (argsNum < _cnt) {\
luaL_error(_state, "Need Get %d But Now Get %d", _cnt, argsNum);\
return _ret;\
}\
}while(0)
#endif

#ifndef PUSH_FUNC
#define PUSH_FUNC do{\
lua_pushlightuserdata(L, (void*)fn);\
lua_pushcclosure(L, proxyFunc, 1);\
lua_setglobal(L, name);\
}while(0)
#endif

    template <typename Ret, typename ...Param>
    struct funcBind{};

    template <typename Ret, typename ...Param>
    struct funcBind<Ret(*)(Param...)> {
        typedef Ret(*func)(Param...);
        static void pushFunc(lua_State *L, const char *name, func fn) {
            PUSH_FUNC;
        }
        static int proxyFunc(lua_State *L) {
            typedef typename __func_traits<func>::Params params;
            ArgList<params> args (L);
            return  __func_traits<func>::call(L, (func)lua_touserdata(L, lua_upvalueindex(1)), args);
        }
    };

    template <typename FUNC>
    void RegisterFunc(lua_State *L, const char *name, FUNC fn) {
        funcBind<FUNC>::pushFunc(L, name, fn);
    }
}

#endif //LUAHOLE_LUAHOLEFUNC_H
