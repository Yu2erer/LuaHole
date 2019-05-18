cmake_minimum_required(VERSION 3.14)
project(luahole)

set(CMAKE_CXX_STANDARD 11)
file(GLOB lua_src "Test/Lua/*.c")

include_directories(Test/Lua/)
include_directories(LuaHole/)

add_executable(LuaHole Test/main.cpp ${lua_src} Test/Student.cpp Test/Student.h)