//
// Created by yu2erer on 2019-05-12.
//

#ifndef LUAHOLE_LUAHOLETRAIT_H
#define LUAHOLE_LUAHOLETRAIT_H
#include "LuaHoleTypeList.h"
#include "LuaHoleHelper.h"

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
        template <typename T, typename FUNC, typename Params>
        static int f(lua_State *L, T *obj, FUNC &fn, TypeListValues<Params> &tvl, __true_type) {
            (obj->*fn)();
            return 0;
        }
        template <typename T, typename FUNC, typename Params>
        static int f(lua_State *L, T *obj, FUNC &fn, TypeListValues<Params> &tvl, __false_type) {
            objPush<Ret>(L, (obj->*fn)());
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
        template <typename T, typename FUNC, typename Params>
        static int f(lua_State *L, T *obj, FUNC &fn, TypeListValues<Params> &tvl, __true_type) {
            (obj->*fn)(tvl.hd);
            return 0;
        }
        template <typename T, typename FUNC, typename Params>
        static int f(lua_State *L, T *obj, FUNC &fn, TypeListValues<Params> &tvl, __false_type) {
            objPush<Ret>(L, (obj->*fn)(tvl.hd));
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
        template <typename T, typename FUNC, typename Params>
        static int f(lua_State *L, T *obj, FUNC &fn, TypeListValues<Params> &tvl, __true_type) {
            (obj->*fn)(tvl.hd, tvl.tl.hd);
            return 0;
        }
        template <typename T, typename FUNC, typename Params>
        static int f(lua_State *L, T *obj, FUNC &fn, TypeListValues<Params> &tvl, __false_type) {
            objPush<Ret>(L, (obj->*fn)(tvl.hd, tvl.tl.hd));
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
        template <typename T, typename FUNC, typename Params>
        static int f(lua_State *L, T *obj, FUNC &fn, TypeListValues<Params> &tvl, __true_type) {
            (obj->*fn)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd);
            return 0;
        }
        template <typename T, typename FUNC, typename Params>
        static int f(lua_State *L, T *obj, FUNC &fn, TypeListValues<Params> &tvl, __false_type) {
            objPush<Ret>(L, (obj->*fn)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd));
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
        template <typename T, typename FUNC, typename Params>
        static int f(lua_State *L, T *obj, FUNC &fn, TypeListValues<Params> &tvl, __true_type) {
            (obj->*fn)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd);
            return 0;
        }
        template <typename T, typename FUNC, typename Params>
        static int f(lua_State *L, T *obj, FUNC &fn, TypeListValues<Params> &tvl, __false_type) {
            objPush<Ret>(L, (obj->*fn)(tvl.hd, tvl.tl.hd, tvl.tl.tl.hd, tvl.tl.tl.tl.hd));
            return 1;
        }
    };

    template <typename Ret, typename FUNC, typename Params>
    inline int doCall(lua_State *L, FUNC &fn, TypeListValues<Params> &tvl) {
        showStack(L);
        typedef typename __ret_void<Ret>::is_void is_void;
        return Caller<Ret, TypeListSize<Params>::value>::f(L, fn, tvl, is_void());
    }

    template <typename T, typename Ret, typename FUNC, typename Params>
    inline int doCall(lua_State *L, T *obj, FUNC &fn, TypeListValues<Params> &tvl) {
        showStack(L);
        typedef typename __ret_void<Ret>::is_void is_void;
        return Caller<Ret, TypeListSize<Params>::value>::f(L, obj, fn, tvl, is_void());
    }

    // Trait<Func>
    template <typename FUNC, typename D = FUNC>
    struct __func_traits {};

    template <typename R, typename D>
    struct __func_traits<R(*)(), D> {
        typedef None Params;
        static int call(lua_State *L, D fn, TypeListValues<Params> tvl) {
            return doCall<R>(L, fn, tvl);
        }
    };

    template <typename R, typename P1, typename D>
    struct __func_traits<R(*)(P1), D> {
        typedef TypeList<P1> Params;
        static int call(lua_State *L, D fn, TypeListValues <Params> tvl) {
            return doCall<R>(L, fn, tvl);
        }
    };

    template <typename R, typename P1, typename P2, typename D>
    struct __func_traits<R(*)(P1, P2), D> {
        typedef TypeList<P1, TypeList<P2>> Params;
        static int call(lua_State *L, D fn, TypeListValues <Params> tvl) {
            return doCall<R>(L, fn, tvl);
        }
    };

    template <typename R, typename P1, typename P2, typename P3, typename D>
    struct __func_traits<R(*)(P1, P2, P3), D> {
        typedef TypeList<P1, TypeList<P2, TypeList<P3>>> Params;
        static int call(lua_State *L, D fn, TypeListValues <Params> tvl) {
            return doCall<R>(L, fn, tvl);
        }
    };

    template <typename R, typename P1, typename P2, typename P3, typename P4, typename D>
    struct __func_traits<R(*)(P1, P2, P3, P4), D> {
        typedef TypeList<P1, TypeList<P2, TypeList<P3, TypeList<P4>>>> Params;
        static int call(lua_State *L, D fn, TypeListValues <Params> tvl) {
            return doCall<R>(L, fn, tvl);
        }
    };

    template <typename T, typename R, typename D>
    struct __func_traits<R(T::*)(), D> {
        typedef None Params;
        static int call(lua_State *L, T *obj, D fn, TypeListValues<Params> tvl) {
            return doCall<T, R>(L, obj, fn, tvl);
        }
    };
}
#endif //LUAHOLE_LUAHOLETRAIT_H
