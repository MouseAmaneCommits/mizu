cmake_minimum_required(VERSION 3.10)

project(mizu)
add_definitions(-DMIZU_BUILD_SHARED -DWIN64)

link_libraries(opengl32 gdi32)
include_directories(../vendor/include)

add_library(mizu SHARED src/core/logger.c src/platform/platform.c src/platform/platform_backend.c src/core/application.c src/renderer/renderer.c src/renderer/context/context.c src/renderer/context/api/opengl_context.c ../vendor/src/glad.c)