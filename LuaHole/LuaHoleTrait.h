//
// Created by yu2erer on 2019-05-12.
//

#ifndef LUAHOLE_LUAHOLETRAIT_H
#define LUAHOLE_LUAHOLETRAIT_H

namespace LuaHole {

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
}
#endif //LUAHOLE_LUAHOLETRAIT_H
