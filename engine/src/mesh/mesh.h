#pragma once

#include "../defines.h"

#include "../renderer/object/vertex_array.h"
#include "../renderer/object/vertex_buffer.h"
#include "../renderer/object/index_buffer.h"
#include "../renderer/object/shader.h"
#include "../renderer/object/texture.h"

#include "../core/optional.h"

typedef struct {
    m_texture* t_albedo;
}m_material;

typedef struct {
    vec3 pos, sca;
    m_material* material;
}m_properties;

struct m_mesh;

typedef struct{
    m_vertex_array* vao;
    m_shader* shader;
    mat4 model;
    m_material* material;

    void(*draw)(struct m_mesh*);
}m_mesh;

MAPI m_mesh* m_create_plane(m_properties* properties);