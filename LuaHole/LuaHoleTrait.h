//
// Created by yu2erer on 2019-05-12.
//

#ifndef LUAHOLE_LUAHOLETRAIT_H
#define LUAHOLE_LUAHOLETRAIT_H
#include "LuaHoleTypeList.h"

namespace LuaHole {

    // Trait<Ret is void?>
    struct __true_type {};
    struct __false_type {};

    template <typename T>
    struct __ret_void {
        typedef __false_type is_void;
    };

    template <>
    struct __ret_void<void> {
        typedef __true_type is_void;
    };


    template <typename Ret, size_t NUM_PARAMS>
    struct Caller {};

    template <typename Ret>
    struct Caller<Ret, 0> {
        template <typename FUNC, typename Params>
        static int f(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl, __true_type) {
            fn();
            return 0;
        }
        template <typename FUNC, typename Params>
        static int f(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl, __false_type) {
            objPush<Ret>(L, fn());
            return 1;
        }
    };

    template <typename Ret>
    struct Caller<Ret, 1> {
        template <typename FUNC, typename Params>
        static int f(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl, __true_type) {
            fn(tvl.hd);
            return 0;
        }
        template <typename FUNC, typename Params>
        static int f(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl, __false_type) {
            objPush<Ret>(L, fn(tvl.hd));
            return 1;
        }
    };

    template <typename Ret>
    struct Caller<Ret, 2> {
        template <typename FUNC, typename Params>
        static int f(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl, __true_type) {
            fn(tvl.hd, tvl.tl.hd);
            return 0;
        }
        template <typename FUNC, typename Params>
        static int f(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl, __false_type) {
            objPush<Ret>(L, fn(tvl.hd, tvl.tl.hd));
            return 1;
        }
    };

    template <typename Ret>
    struct Caller<Ret, 3> {
        template <typename FUNC, typename Params>
        static int f(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl, __true_type) {
            fn(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd);
            return 0;
        }
        template <typename FUNC, typename Params>
        static int f(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl, __false_type) {
            objPush<Ret>(L, fn(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd));
            return 1;
        }
    };

    template <typename Ret>
    struct Caller<Ret, 4> {
        template <typename FUNC, typename Params>
        static int f(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl, __true_type) {
            fn(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd);
            return 0;
        }
        template <typename FUNC, typename Params>
        static int f(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl, __false_type) {
            objPush<Ret>(L, fn(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd));
            return 1;
        }
    };

    template <typename Ret, typename FUNC, typename Params>
    inline int doCall(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl, __true_type) {
        showStack(L);
        return Caller<Ret, TypeListSize<Params>::value>::f(L, fn, tvl, __true_type());
    }

    template <typename Ret, typename FUNC, typename Params>
    inline int doCall(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl, __false_type) {
        showStack(L);
        return Caller<Ret, TypeListSize<Params>::value>::f(L, fn, tvl, __false_type());
    }

    // Trait<Func>
    template <typename FUNC, typename D = FUNC>
    struct __func_traits {};

    template <typename R, typename D>
    struct __func_traits<R(*)(), D> {
        typedef None Params;
        typedef typename __ret_void<R>::is_void is_void;
        static int call(lua_State *L, D fn, TypeListValues<Params> tvl) {
            return doCall<R>(L, fn, tvl, is_void());
        }
    };

    template <typename R, typename P1, typename D>
    struct __func_traits<R(*)(P1), D> {
        typedef TypeList<P1> Params;
        typedef typename __ret_void<R>::is_void is_void;
        static int call(lua_State *L, D fn, TypeListValues <Params> tvl) {
            return doCall<R>(L, fn, tvl, is_void());
        }
    };

    template <typename R, typename P1, typename P2, typename D>
    struct __func_traits<R(*)(P1, P2), D> {
        typedef TypeList<P1, TypeList<P2>> Params;
        typedef typename __ret_void<R>::is_void is_void;
        static int call(lua_State *L, D fn, TypeListValues <Params> tvl) {
            return doCall<R>(L, fn, tvl, is_void());
        }
    };

    template <typename R, typename P1, typename P2, typename P3, typename D>
    struct __func_traits<R(*)(P1, P2, P3), D> {
        typedef TypeList<P1, TypeList<P2, TypeList<P3>>> Params;
        typedef typename __ret_void<R>::is_void is_void;
        static int call(lua_State *L, D fn, TypeListValues <Params> tvl) {
            return doCall<R>(L, fn, tvl, is_void());
        }
    };

    template <typename R, typename P1, typename P2, typename P3, typename P4, typename D>
    struct __func_traits<R(*)(P1, P2, P3, P4), D> {
        typedef TypeList<P1, TypeList<P2, TypeList<P3, TypeList<P4>>>> Params;
        typedef typename __ret_void<R>::is_void is_void;
        static int call(lua_State *L, D fn, TypeListValues <Params> tvl) {
            return doCall<R>(L, fn, tvl, is_void());
        }
    };

}
#endif //LUAHOLE_LUAHOLETRAIT_H
