//
// Created by yu2erer on 2019-05-12.
//

#ifndef LUAHOLE_LUAHOLEFUNC_H
#define LUAHOLE_LUAHOLEFUNC_H
#include "LuaHeader.h"
#include "LuaHoleTrait.h"
#include "LuaHolePush.h"
#include "LuaHoleTypeList.h"
#include "LuaHoleHelper.h"

namespace LuaHole {

#ifndef BIND_CHECK_FUNC_ARG_NUM
#define BIND_CHECK_FUNC_ARG_NUM(_state, _cnt, _ret) do{\
int argsNum = lua_gettop(_state);\
if (argsNum < _cnt) {\
luaL_error(_state, "At least %d But Now Only Get %d", _cnt, argsNum);\
return _ret;\
}\
}while(0)
#endif

    template <typename Ret, typename ...Param>
    struct funcBind{};

    template <typename Ret, typename ...Param>
    struct funcBind<Ret(*)(Param...)> {
        typedef Ret(*func)(Param...);
        static void pushFunc(lua_State *L, const char *name, func fn) {
            lua_pushlightuserdata(L, (void*)fn);
            lua_pushcclosure(L, proxyFunc, 1);
            lua_setglobal(L, name);
        }
        static int proxyFunc(lua_State *L) {
            showStack(L);
            typedef typename __func_traits<func>::Params params;
            BIND_CHECK_FUNC_ARG_NUM(L, TypeListSize<params>::value, 0);
            ArgList<params> args (L);
            lua_pop(L, int(TypeListSize<params>::value));
            return  __func_traits<func>::call(L, (func)lua_touserdata(L, lua_upvalueindex(1)), args);
        }
    };

    template <typename FUNC>
    inline void RegisterFunc(lua_State *L, const char *name, FUNC fn) {
        funcBind<FUNC>::pushFunc(L, name, fn);
    }
}

#endif //LUAHOLE_LUAHOLEFUNC_H
