cmake_minimum_required(VERSION 3.10)

project(editor)

link_directories(../engine/build)
link_libraries(libmizu.dll.a)
add_definitions(-DWIN64)

add_executable(editor src/editor.c src/main.c)