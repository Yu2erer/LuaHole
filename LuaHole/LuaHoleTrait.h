//
// Created by yu2erer on 2019-05-12.
//

#ifndef LUAHOLE_LUAHOLETRAIT_H
#define LUAHOLE_LUAHOLETRAIT_H

namespace LuaHole {

    struct __true_type {};
    struct __false_type {};

    template <typename T>
    struct __retVoid {
        typedef __false_type isVoid;
    };

    template <>
    struct __retVoid<void> {
        typedef __true_type isVoid;
    };
}
#endif //LUAHOLE_LUAHOLETRAIT_H
