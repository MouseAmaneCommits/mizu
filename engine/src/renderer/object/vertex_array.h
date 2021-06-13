#pragma once

#include "../../defines.h"
#include "vertex_buffer.h"

#define MAX_VBO_COUNT 16

struct m_vertex_array;

typedef struct {
    void* unimplemented_data;

    m_vertex_buffer* vbos[MAX_VBO_COUNT];
    u32 vbo_index;

    void(*bind)(struct m_vertex_array*);
    void(*unbind)(struct m_vertex_array*);
    void(*add_vbo)(struct m_vertex_array*, m_vertex_buffer*);
    void(*draw)(struct m_vertex_array*);
}m_vertex_array;