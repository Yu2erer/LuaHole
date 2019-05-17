//
// Created by yu2erer on 2019/5/17.
//

#ifndef LUAHOLE_LUAHOLECLASSNAME_H
#define LUAHOLE_LUAHOLECLASSNAME_H

namespace LuaHole {

    template <typename T>
    class ClassName {
    public:
        static void setName(const char *name) {
            m_classname = name;
        }
        static const char *getName() {
            return m_classname.c_str();
        }
    private:
        static std::string m_classname;
    };

    template<typename T>
    std::string ClassName<T>::m_classname;
}

#endif //LUAHOLE_LUAHOLECLASSNAME_H
