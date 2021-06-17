#include "mesh.h"

#include "../../memory/mmemory.h"
#include <memory.h>

#include "../../core/logger.h"

/*- Globals -*/
static f32 m_quad_vertices[] = {
     0.5f,  0.5f, 0.0f,  
     0.5f, -0.5f, 0.0f,  
    -0.5f, -0.5f, 0.0f,  
    -0.5f,  0.5f, 0.0f   
};

static u32 m_quad_indices[] = {
    0, 1, 3,
    1, 2, 3 
};

static float m_quad_tex_coords[] = {
1.0f, 1.0f,
1.0f, 0.0f,
0.0f, 0.0f,
0.0f, 1.0f 
};


void m_init_mesh2d(m_mesh2d* self, u32 sprite_type, const char* texture_name){

    // Pre initialization
    self->vao = (m_vertex_array *)m_allocate(sizeof(m_vertex_array));
    self->shader = (m_shader *)m_allocate(sizeof(m_shader));
    self->component = (m_sprite_component *)m_allocate(sizeof(m_sprite_component));
    m_vertex_buffer *buffer = (m_vertex_buffer *)m_allocate(sizeof(m_vertex_buffer));
    m_vertex_buffer* tex_buf = (m_vertex_buffer*)m_allocate(sizeof(m_vertex_buffer));
    m_index_buffer *ibo = (m_index_buffer *)m_allocate(sizeof(m_index_buffer));
    m_texture *texture = (m_texture *)m_allocate(sizeof(m_texture));
    memset(self->vao, 0, sizeof(m_vertex_array));
    memset(ibo, 0, sizeof(m_index_buffer));
    memset(buffer, 0, sizeof(m_vertex_buffer));
    memset(self->shader, 0, sizeof(m_shader));
    memset(self->component, 0, sizeof(m_sprite_component));
    memset(texture, 0, sizeof(m_texture));
    memset(tex_buf, 0, sizeof(m_vertex_buffer));

    // Initialization
    m_init_vertex_array(self->vao);

    switch(sprite_type){
        case M_QUAD:
            m_init_vertex_buffer(buffer, m_quad_vertices, sizeof(m_quad_vertices));
            m_init_vertex_buffer(tex_buf, m_quad_tex_coords, sizeof(m_quad_tex_coords));
            m_init_index_buffer(ibo, m_quad_indices, sizeof(m_quad_indices));
            break;
        default:
            M_ERROR("no other sprite types supported");
            return;
    }

    m_init_shader(self->shader, "vertex_shader.vs.glsl", "fragment_shader.fs.glsl");
    m_init_texture(texture, 0, texture_name);

    m_vertex_buffer_layout *layout = (m_vertex_buffer_layout *)m_allocate(sizeof(m_vertex_buffer_layout));
    memset(layout, 0, sizeof(m_vertex_buffer_layout));
    layout->index = 0;
    layout->size = 3;
    m_vertex_buffer_layout *another_layout = (m_vertex_buffer_layout *)m_allocate(sizeof(m_vertex_buffer_layout));
    memset(another_layout, 0, sizeof(m_vertex_buffer_layout));
    another_layout->index = 1;
    another_layout->size = 2;

    buffer->set_layout(buffer, layout);
    tex_buf->set_layout(tex_buf, another_layout);

    self->vao->add_vbo(self->vao, buffer);
    self->vao->add_vbo(self->vao, tex_buf);

    self->vao->bind_ibo(self->vao, ibo);
    self->component->sprite_flag = M_USE_TEXTURE;
    self->component->texture = texture;
}

void m_render_mesh2d(m_mesh2d* mesh, mat4* view, mat4* model, mat4* proj){
    if(mesh->component->sprite_flag & M_USE_TEXTURE) mesh->component->texture->bind(mesh->component->texture);
    mesh->vao->bind(mesh->vao);
    mesh->shader->bind(mesh->shader);
    mesh->shader->set_int(mesh->shader, "tex", 0);
    mesh->shader->set_mat4(mesh->shader, "view", *view);
    mesh->shader->set_mat4(mesh->shader, "proj", *proj);
    mesh->shader->set_mat4(mesh->shader, "model", *model);

    mesh->vao->draw(mesh->vao);

    mesh->shader->unbind(mesh->shader);
    mesh->vao->unbind(mesh->vao);
    if(mesh->component->sprite_flag & M_USE_TEXTURE) mesh->component->texture->unbind(mesh->component->texture);
}