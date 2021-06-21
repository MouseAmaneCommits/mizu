#pragma once

#include "context/context.h"
#include "../defines.h"
#include "../platform/platform.h"
#include "object/vertex_array.h"
#include "object/shader.h"
#include "object/texture.h"

typedef struct {
    m_vertex_array* array;
    m_shader* shader;
    m_texture* o_texture; b8 uses_texture; // optional
    mat4* model;
}m_package;

#define INITIAL_TOTAL_PACKAGE_SIZE 1000
typedef struct {
    m_package* packages[INITIAL_TOTAL_PACKAGE_SIZE];
    u32 front, rear, size;
    u32 capacity;
}m_render_queue;

typedef struct {
    mat4 view;
    mat4 proj;
    float o_clear_color[4]; // r,g,b,a
}m_camera;

MAPI void m_init_renderer(m_platform* platform, m_renderer_api api);
MAPI void m_begin_frame();
MAPI void m_bind_camera(m_camera* camera);
MAPI void m_submit(m_vertex_array* array, m_shader* shader, mat4* model);
MAPI void m_submit_with_texture(m_vertex_array* array, m_shader* shader, m_texture* texture, mat4* model);

MAPI void m_flush();
MAPI void m_end_frame();

MAPI void m_reshape_renderer(u32 width, u32 height);
MAPI b8 m_initialized_renderer();

MAPI m_renderer_api m_renderer_get_api();