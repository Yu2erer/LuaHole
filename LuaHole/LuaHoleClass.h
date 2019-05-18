//
// Created by yu2erer on 2019/5/15.
//

#ifndef LUAHOLE_LUAHOLECLASS_H
#define LUAHOLE_LUAHOLECLASS_H
#include "LuaHeader.h"
#include "LuaHoleTypeList.h"
#include "LuaHoleFunc.h"
#include "LuaHoleUserData.h"
#include "LuaHoleClassName.h"

namespace LuaHole {

    template <typename T>
    inline int __gc(lua_State *L) {
        UserData<T>** ud = static_cast<UserData<T>**>(luaL_checkudata(L, -1, ClassName<T>::getName()));
        delete (*ud);
        return 0;
    }

    template <typename T>
    inline void RegClass(lua_State *L, const char *name) {
        ClassName<T>::setName(name);

        luaL_newmetatable(L, name);
        lua_pushstring(L, "__index");
        lua_pushvalue(L, -2);
        lua_settable(L, -3);

        lua_pushstring(L, "__newindex");
        lua_pushvalue(L, -2);
        lua_settable(L, -3);

        lua_pushstring(L, "__gc");
        lua_pushcfunction(L, &__gc<T>);
        lua_rawset(L, -3);
        lua_pop(L, 1);
        assert(lua_gettop(L) == 0);
    }

    template <typename T, typename FUNC>
    inline int proxyCtor(lua_State *L) {
        typedef typename __func_traits<FUNC>::Params params;
        ArgList<params> args(L);
        lua_pop(L, int(TypeListSize<params>::value));
        showStack(L);
        return __func_traits<FUNC>::template call<T>(L, args);
    }

    template <typename T, typename FUNC>
    inline void RegCtor(lua_State *L) {
        lua_pushcclosure(L, &proxyCtor<T, FUNC>, 0);
        lua_setglobal(L, ClassName<T>::getName());
    }

    template <typename FUNC>
    inline void RegMethod(lua_State *L, const char *name, FUNC fn) {
        funcBind<FUNC>::pushFunc(L, name, fn);
    }

}

#endif //LUAHOLE_LUAHOLECLASS_H
