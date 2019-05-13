//
// Created by yu2erer on 2019-05-12.
//

#ifndef LUAHOLE_LUAHOLEFUNC_H
#define LUAHOLE_LUAHOLEFUNC_H
#include "LuaHeader.h"
#include "LuaHoleTrait.h"
#include "LuaHolePush.h"

namespace LuaHole {

#ifndef BIND_CHECK_FUNC_ARG_NUM
#define BIND_CHECK_FUNC_ARG_NUM(_state, _cnt, _ret) do{\
int num = lua_gettop(_state);\
if (num < _cnt) {\
luaL_error(_state, "Need Get %d But Now Get %d", _cnt, num);\
return _ret;\
}\
}while(0)
#endif

#ifndef PUSH_FUNC
#define PUSH_FUNC do{\
lua_pushlightuserdata(L, (void*)func);\
lua_pushcclosure(L, proxyFunc, 1);\
lua_setglobal(L, name);\
}while(0)
#endif
    int __type_helper(lua_State *L);

    template <typename Ret>
    class funcBind{};

    template <typename Ret>
    class funcBind<Ret(*)()> {
    public:
        static void pushFunc(lua_State *L, const char *name, Ret(*func)()) {
            PUSH_FUNC;
        }
        static int proxyFunc(lua_State *L) {
            typedef typename __ret_void<Ret>::is_void is_void;
            return doCall<Ret>(L, (func)lua_touserdata(L, lua_upvalueindex(1)), is_void());
        }
    private:
        typedef Ret(*func)();
        template <typename Result>
        static int doCall(lua_State *L, func fn, __false_type) {
            objPush<Result>(L, fn());
            return 1;
        }
        template <typename Result>
        static int doCall(lua_State *L, func fn, __true_type) {
            fn();
            return 0;
        }
    };

    template <typename Ret, typename Arg1>
    class funcBind<Ret(*)(Arg1)> {
    public:
        static void pushFunc(lua_State *L, const char *name, Ret(*func)(Arg1)) {
            PUSH_FUNC;
        }
        static int proxyFunc(lua_State *L) {
            BIND_CHECK_FUNC_ARG_NUM(L, 1, 0);
            Arg1 arg1 = popValue<Arg1>(L);
            typedef typename __ret_void<Ret>::is_void is_void;
            return doCall<Ret>(L, (func)lua_touserdata(L, lua_upvalueindex(1)), arg1, is_void());
        }
    private:
        typedef Ret(*func)(Arg1);
        template <typename Result>
        static int doCall(lua_State *L, func fn, const Arg1 &arg1, __false_type) {
            objPush<Result>(L, fn(arg1));
            return 1;
        }
        template <typename Result>
        static int doCall(lua_State *L, func fn,  const Arg1 &arg1, __true_type) {
            fn(arg1);
            return 0;
        }
    };

    template <typename Ret, typename Arg1>
    class funcBind<Ret(*)(Arg1, ...)> {
    public:
        static void pushFunc(lua_State *L, const char *name, Ret(*func)(Arg1, ...)) {
            PUSH_FUNC;
        }
        static int proxyFunc(lua_State *L) {
            // 从 lua 栈中不断获取参数 转发给 docall 再发给 fn
            int top = lua_gettop(L);
            Arg1 arg1 = popValue<Arg1>(L);
            typedef typename __ret_void<Ret>::is_void is_void;
            return doCall<Ret>(L, (func)lua_touserdata(L, lua_upvalueindex(1)), arg1, is_void());
        }
    private:
        typedef Ret(*func)(Arg1, ...);
        template <typename Result>
        static int doCall(lua_State *L, func fn, const Arg1 &arg1, __false_type) {
            objPush<Result>(L, fn(arg1, 13));
            return 1;
        }
        template <typename Result>
        static int doCall(lua_State *L, func fn, const Arg1 &arg1, __true_type) {
            fn(arg1, 13);
            return 0;
        }
    };

    template <typename FUNC>
    void RegisterFunc(lua_State *L, const char *name, FUNC fn) {
        funcBind<FUNC>::pushFunc(L, name, fn);
    }
//
//    int __type_helper(lua_State *L) {
//        int type = lua_type(L, -1);
//        switch (type) {
//            case LUA_TBOOLEAN:
//                return LUA_TBOOLEAN;
//
//            default:
//        }
//    }
}

#endif //LUAHOLE_LUAHOLEFUNC_H
