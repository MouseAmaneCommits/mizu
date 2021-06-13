cmake_minimum_required(VERSION 3.10)

project(testbed)
link_directories(../engine/build)
link_libraries(libmizu.dll.a)
add_definitions(-DWIN64)
include_directories(../vendor/include)

add_executable(testbed src/main.c ../vendor/src/glad.c)