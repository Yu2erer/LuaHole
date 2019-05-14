//
// Created by yu2erer on 2019/5/14.
//

#ifndef LUAHOLE_LUAHOLEHELPER_H
#define LUAHOLE_LUAHOLEHELPER_H

namespace LuaHole {

    static inline const char *stackValue2Str(lua_State *L, int index);

#define DDebug
#ifdef DDebug
#define DEBUG(fmt, ...) printf("[%s][%d]: %s\n" , __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
    static inline void showStack(lua_State *L, const char *msg = NULL) {
        int top = lua_gettop(L);
        if (msg) {
            printf("top:%d,%s\n", top, msg);
        } else {
            printf("top:%d\n", top);
        }
        int i;
        for (i = top; i > 0; --i) {
            if (i == top) {
                printf("(stack index:%d) %s <- top\n", i, stackValue2Str(L, i));
            } else {
                printf("(stack index:%d) %s\n", i, stackValue2Str(L, i));
            }
        }
    }
#else
#define DEBUG(fmt, ...)
#define showStack(L, M);
#endif

    static inline const char *stackValue2Str(lua_State *L, int index) {
        static char buff[1024];
        int type = lua_type(L, index);
        switch (type) {
            case LUA_TNIL:
                snprintf(buff, 1023, "nil");
                break;
            case LUA_TUSERDATA:
                snprintf(buff, 1023, "userdata");
                break;
            case LUA_TLIGHTUSERDATA:
                snprintf(buff, 1023, "lightuserdata");
                break;
            case LUA_TNUMBER: {
                lua_Number v = lua_tonumber(L, index);
                if (v != (lua_Integer) v) {
                    snprintf(buff, 1023, "%f", v);
                } else {
                    snprintf(buff, 1023, "%lld", lua_tointeger(L, index));
                }
            }
                break;
            case LUA_TBOOLEAN: {
                lua_Integer b = lua_tointeger(L, index);
                snprintf(buff, 1023, "%s", b == 1 ? "true" : "false");
            }
                break;
            case LUA_TTABLE:
                snprintf(buff, 1023, "table");
                break;
            case LUA_TTHREAD:
                snprintf(buff, 1023, "thread");
                break;
            case LUA_TFUNCTION:
                snprintf(buff, 1023, "function");
                break;
            case LUA_TSTRING:
                snprintf(buff, 1023, "%s", lua_tostring(L, index));
                break;
            default:
                snprintf(buff, 1023, "unknow");
        }
        buff[1023] = 0;
        return buff;
    }
}

#endif //LUAHOLE_LUAHOLEHELPER_H
