//
// Created by yu2erer on 2019/5/13.
//

#ifndef LUAHOLE_LUAHOLETYPELIST_H
#define LUAHOLE_LUAHOLETYPELIST_H
#include <string>
#include <typeinfo>
#include "LuaHeader.h"
#include "LuaHolePop.h"
#include "LuaHoleHelper.h"

namespace LuaHole {

    typedef void None;

    template <typename Head, typename Tail = None>
    struct TypeList { typedef Tail TailType; };

    template <typename List>
    struct TypeListSize {
        static const size_t value = TypeListSize<typename List::TailType>::value + 1;
    };

    template <>
    struct TypeListSize<None> {
        static const size_t value = 0;
    };

    template <typename List>
    struct TypeListValues {
        static const std::string tostring(bool) { return ""; }
    };

    template <typename Head, typename Tail>
    struct TypeListValues <TypeList <Head, Tail>> {
        Head hd;
        TypeListValues <Tail> tl;
        TypeListValues(Head hd, TypeListValues <Tail> const &tl) : hd(hd), tl(tl) { }
        static const std::string tostring(bool comma = false) {
            std::string s;
            if (comma) { s = ", "; }
            s = s + typeid(Head).name();
            return s + TypeListValues<Tail>::tostring(true);
        }
    };

    template <typename List, int Start = 1>
    struct ArgList {};

    template <int Start>
    struct ArgList <None, Start> : public TypeListValues <None> {
        ArgList(lua_State *) { }
    };

    template <typename Head, typename Tail, int Start>
    struct ArgList <TypeList <Head, Tail>, Start>
            : public TypeListValues <TypeList <Head, Tail>> {
        ArgList(lua_State *L)
         : TypeListValues <TypeList <Head, Tail>> (LuaHole::Get<Head>(L, Start), ArgList <Tail, Start + 1> (L)) { }
    };

}

#endif //LUAHOLE_LUAHOLETYPELIST_H
