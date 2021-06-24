#pragma once

#include "../defines.h"

#include "../renderer/object/vertex_array.h"
#include "../renderer/object/vertex_buffer.h"
#include "../renderer/object/index_buffer.h"
#include "../renderer/object/shader.h"
#include "../renderer/object/texture.h"

#include "../core/optional.h"

typedef struct {
    vec3 pos, sca;
}m_properties;

typedef struct{
    m_vertex_array* vao;
    m_shader* shader;
}m_mesh;

MAPI m_mesh* m_create_plane(m_properties* properties);