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
#include "LuaHolePop.h"
#include "LuaHoleUserData.h"
#include "LuaHoleClassName.h"

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

    inline bool checkCall(lua_State *L, const char *name) {
        lua_getglobal(L, name);
        if (lua_type(L, -1) != LUA_TFUNCTION) {
            lua_pop(L, 1);
            DEBUG("This function does not exist");
            return false;
        }
        return true;
    }

    template <typename Ret>
    inline Ret doCall(lua_State *L, int argsNum, int errFunc) {
        if (lua_pcall(L, argsNum, 1, errFunc) != 0) {
            const char *err = lua_tostring(L, -1);
            DEBUG(err);
            lua_pop(L, -1);
        }
        return Get<Ret>(L, -1);
    }

    template <>
    inline void doCall(lua_State *L, int argsNum, int errFunc) {
        if (lua_pcall(L, argsNum, 0, errFunc) != 0) {
            const char *err = lua_tostring(L, -1);
            DEBUG(err);
            lua_pop(L, -1);
        }
    }

    template <typename Ret>
    Ret Call(lua_State *L, const char *name) {
        if (!checkCall(L, name)) { return Ret(); }
        return doCall<Ret>(L, 0, 0);
    }

    template <typename Ret, typename Arg1>
    Ret Call(lua_State *L, const char *name, const Arg1 &arg1) {
        if (!checkCall(L, name)) { return Ret(); }
        objPush<Arg1>(L, arg1);
        return doCall<Ret>(L, 1, 0);
    }

    template <typename Ret, typename Arg1, typename Arg2>
    Ret Call(lua_State *L, const char *name, const Arg1 &arg1, const Arg2 &arg2) {
        if (!checkCall(L, name)) { return Ret(); }
        objPush<Arg1>(L, arg1);
        objPush<Arg2>(L, arg2);
        return doCall<Ret>(L, 2, 0);
    }

    template <typename Ret, typename Arg1, typename Arg2, typename Arg3>
    Ret Call(lua_State *L, const char *name, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3) {
        if (!checkCall(L, name)) { return Ret(); }
        objPush<Arg1>(L, arg1);
        objPush<Arg2>(L, arg2);
        objPush<Arg3>(L, arg3);
        return doCall<Ret>(L, 3, 0);
    }

    template <typename Ret, typename Arg1, typename Arg2, typename Arg3, typename Arg4>
    Ret Call(lua_State *L, const char *name, const Arg1 &arg1, const Arg2 &arg2, const Arg3 &arg3, const Arg4 &arg4) {
        if (!checkCall(L, name)) { return Ret(); }
        objPush<Arg1>(L, arg1);
        objPush<Arg2>(L, arg2);
        objPush<Arg3>(L, arg3);
        objPush<Arg4>(L, arg4);
        return doCall<Ret>(L, 4, 0);
    }

    template <typename Ret, typename ...Param>
    struct funcBind{};

    template <typename Ret, typename ...Param>
    struct funcBind<Ret(*)(Param...)> {
        typedef Ret(*func)(Param...);
        static void pushFunc(lua_State *L, const char *name, func fn) {
            lua_pushlightuserdata(L, (void*)fn);
            lua_pushcclosure(L, &proxyFunc, 1);
            lua_setglobal(L, name);
        }
        static int proxyFunc(lua_State *L) {
            showStack(L);
            typedef typename __func_traits<func>::Params params;
            BIND_CHECK_FUNC_ARG_NUM(L, TypeListSize<params>::value, 0);
            ArgList<params> args(L);
            lua_pop(L, int(TypeListSize<params>::value));
            return  __func_traits<func>::call(L, (func)lua_touserdata(L, lua_upvalueindex(1)), args);
        }
    };

    template<typename T>
    inline int inject(lua_State *L, T *obj) {
        UserData<T>** ud = static_cast<UserData<T>**>(lua_newuserdata(L, sizeof(UserData<T>*)));
        *ud = new UserData<T>(obj);

        luaL_getmetatable(L, ClassName<T>::getName());
        lua_setmetatable(L, -2);
        return 1;
    }

    template<typename T>
    inline int constructor(lua_State *L) {
        return inject<T>(L, new T());
    }

    template <typename Ret, typename T, typename ...Param>
    struct funcBind<Ret(T::*)(Param...)> {
        typedef Ret(T::*func)(Param...);
        typedef typename __func_traits<func>::Params params;
        static void pushFunc(lua_State *L, const char *name, func fn) {
            luaL_getmetatable(L, ClassName<T>::getName());
            lua_pushstring(L, name);
            new (lua_newuserdata(L, sizeof(func))) func(fn);
            lua_pushcclosure(L, &proxyFunc, 1);
            lua_rawset(L, -3);
            lua_pop(L, 1);
        }
        static int proxyFunc(lua_State *L) {
            showStack(L);
            T *obj = (T*)lua_touserdata(L, 1);
            ArgList<params, 2> args(L);
            lua_pop(L, int(TypeListSize<params>::value) + 1);
            const func& fn = *static_cast<const func*>(lua_touserdata(L, lua_upvalueindex(1)));
            return  __func_traits<func>::call(L, obj, fn, args);
        }
    };

    template <typename FUNC>
    inline void RegFunc(lua_State *L, const char *name, FUNC fn) {
        funcBind<FUNC>::pushFunc(L, name, fn);
    }
}

#endif //LUAHOLE_LUAHOLEFUNC_H
