cmake_minimum_required(VERSION 3.10)

project(mizu)
add_definitions(-DMIZU_BUILD_SHARED -DWIN64)

link_libraries(opengl32 gdi32)
include_directories(../vendor/include)

option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)

add_library(mizu SHARED src/core/logger.c src/platform/platform.c src/platform/platform_backend.c src/core/application.c src/renderer/renderer.c src/renderer/context/context.c src/renderer/context/api/opengl_context.c src/renderer/object/opengl/ogl_vertex_array.c src/renderer/object/opengl/ogl_vertex_buffer.c src/renderer/object/opengl/ogl_shader.c src/math/mat4.c src/math/vector.c src/renderer/object/opengl/ogl_index_buffer.c src/renderer/object/opengl/ogl_texture.c ../vendor/src/glad.c)