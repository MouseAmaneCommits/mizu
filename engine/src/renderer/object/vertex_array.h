#pragma once

#include "../../defines.h"
#include "vertex_buffer.h"
#include "index_buffer.h"

#define MAX_VBO_COUNT 16

struct m_vertex_array;

typedef enum{
    PRIMITIVE_TRIANGLES=0,
    PRIMITIVE_QUADS=1
}m_primitive_type;

typedef struct {
    void* unimplemented_data;

    m_vertex_buffer* vbos[MAX_VBO_COUNT];
    u32 vbo_index;

    m_index_buffer* ibo;
    b8 ibo_bound;

    void(*bind)(struct m_vertex_array*);
    void(*unbind)(struct m_vertex_array*);
    void(*add_vbo)(struct m_vertex_array*, m_vertex_buffer*);
    void(*draw)(struct m_vertex_array*);
    void(*bind_ibo)(struct m_vertex_array*, m_index_buffer*);

    m_primitive_type o_primitive_type;
}m_vertex_array;

MAPI void m_init_vertex_array(m_vertex_array* vao);
MAPI void m_destroy_vertex_array(m_vertex_array* vao);