#pragma once

#include "../vertex_buffer.h"
#include "../../../defines.h"

MAPI void m_init_vertex_buffer_opengl(m_vertex_buffer* vbo, float* vertices, u32 size_of_vertices);
MAPI void m_destroy_vertex_buffer_opengl(m_vertex_buffer* vbo);