cmake_minimum_required(VERSION 3.14)
project(luahole)

set(CMAKE_CXX_STANDARD 11)
file(GLOB lua_src "lua/*.c")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include_directories(lua/)
add_executable(LuaHole main.cpp ${lua_src} LuaHole/LuaHeader.h LuaHole/LuaHole.h LuaHole/LuaPopValue.h LuaHole/LuaPushValue.h)