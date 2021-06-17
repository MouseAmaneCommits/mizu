#pragma once

#include "../../math/mat4.h"
#include "../../defines.h"
#include "../object/texture.h"
#include "../object/vertex_array.h"
#include "../object/shader.h"

/*- Sprite structures -*/
typedef enum{
    M_TRIANGLE,
    M_QUAD,
}m_sprite_type_enumeration;

typedef enum{
    M_USE_TEXTURE=0x00000005,
    M_USE_COLOR=0x00000008
}m_sprite_component_enumeration;

typedef struct {
    vec4 color;
    m_texture* texture;
    
    u32 sprite_flag;
}m_sprite_component;

typedef struct {
    const char* tag;
}m_tag;

typedef struct {
    m_sprite_component* component;
}m_sprite;

/*- Mesh structures -*/
typedef struct {
    m_sprite_component* component;
    m_vertex_array* vao;
    m_shader* shader;
}m_mesh2d;

/*- Mesh functions -*/
MAPI void m_init_mesh2d(m_mesh2d* mesh, u32 sprite_type, const char* texture_name);

MAPI void m_render_mesh2d(m_mesh2d* mesh, mat4* view, mat4* model, mat4* proj);