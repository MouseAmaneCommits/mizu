#pragma once

#include "../../defines.h"

typedef struct {
    u32 index;
    u32 size;
}m_vertex_buffer_layout;

struct m_vertex_buffer;

typedef struct {
    void* unimplemented_data;

    u32 length;
    m_vertex_buffer_layout layout;
    void(*bind)(struct m_vertex_buffer*);
    void(*unbind)(struct m_vertex_buffer*);
    void(*set_layout)(struct m_vertex_buffer*, m_vertex_buffer_layout*);
}m_vertex_buffer;

MAPI void m_init_vertex_buffer(m_vertex_buffer* vbo, float* vertices, u32 size);
MAPI void m_destory_vertex_buffer(m_vertex_buffer* vbo);