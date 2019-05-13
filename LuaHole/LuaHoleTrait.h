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

    // Trait<Func>
    template <typename FUNC, typename D = FUNC>
    struct __func_traits {};

    template <typename R, typename D>
    struct __func_traits<R(*)(), D> {
        typedef D DeclType;
        typedef R Returntype;
        typedef None Params;
        static R call(D fn, TypeListValues <Params> tvl) {

        }
    };

    template <typename R, typename P1, typename D>
    struct __func_traits<R(*)(P1), D> {
        typedef D DeclType;
        typedef R Returntype;
        typedef TypeList<P1> Params;
        static R call(D fn, TypeListValues <Params> tvl) {

        }
    };

}
#endif //LUAHOLE_LUAHOLETRAIT_H
