cmake_minimum_required(VERSION 3.14)
project(luahole)

set(CMAKE_CXX_STANDARD 11)
file(GLOB lua_src "Lua/*.c")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include_directories(Lua/)
include_directories(LuaHole/)

add_executable(LuaHole main.cpp ${lua_src})