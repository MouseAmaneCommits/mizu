cmake_minimum_required(VERSION 3.10)

project(mizu)
add_definitions(-DMIZU_BUILD_SHARED -DWIN64)

link_libraries(opengl32 gdi32 pthread)
include_directories(../vendor/include)

option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)

add_library(mizu SHARED
src/utils/array.c 
src/core/logger.c 
src/memory/mmemory.c
src/platform/platform.c src/platform/platform_backend.c 
src/core/application.c 
src/renderer/object/index_buffer.c src/renderer/object/shader.c src/renderer/object/texture.c src/renderer/object/vertex_array.c src/renderer/object/vertex_buffer.c src/renderer/object/uniform_buffer.c
src/renderer/renderer.c src/renderer/context/context.c src/renderer/context/api/opengl_context.c 
src/renderer/object/opengl/ogl_vertex_array.c src/renderer/object/opengl/ogl_vertex_buffer.c src/renderer/object/opengl/ogl_shader.c src/renderer/object/opengl/ogl_index_buffer.c src/renderer/object/opengl/ogl_texture.c src/renderer/object/opengl/ogl_uniform_buffer.c
src/math/mat4.c src/math/vector.c 
../vendor/src/glad.c
src/scripting/script.c
src/performance/performance.c
src/mesh/mesh.c
)