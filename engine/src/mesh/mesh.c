#include "mesh.h"

#include <memory.h>
#include <malloc.h>

m_mesh* m_create_plane(m_properties* properties){
    // allocations
    m_mesh* mesh = QUICK_MALLOC(m_mesh);
    memset(mesh, 0, sizeof(m_mesh));
    mesh->vao = QUICK_MALLOC(m_vertex_array);
    memset(mesh->vao, 0, sizeof(m_vertex_array));
    mesh->shader = QUICK_MALLOC(m_shader);
    memset(mesh->shader, 0, sizeof(m_shader));

    // object data
    f32 vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};
    f32 texture_coords[] = {
        // texture coords
        1.0f, 1.0f, // top right
        1.0f, 0.0f, // bottom ri
        0.0f, 0.0f, // bottom le
        0.0f, 1.0f  // top left
    };

    u32 indices[] = {
        0, 1, 3,
        1, 2, 3};

    m_vertex_buffer_layout layout;
    layout.index = 0;
    layout.size = 3;

    // initializations
    m_init_vertex_array(mesh->vao);
    m_init_shader(mesh->shader, "vertex_shader.vs.glsl", "fragment_shader.fs.glsl");
    CREATE(m_vertex_buffer, m_init_vertex_buffer(vbo, vertices, sizeof(vertices)), vbo);
    vbo->set_layout(vbo, &layout);
    CREATE(m_vertex_buffer, m_init_vertex_buffer(tvbo, texture_coords, sizeof(texture_coords)), tvbo);
    layout.index = 1; layout.size = 2;
    tvbo->set_layout(tvbo, &layout);
    CREATE(m_index_buffer, m_init_index_buffer(ibo, indices, sizeof(indices)), ibo);
    mesh->vao->add_vbo(mesh->vao, vbo);
    mesh->vao->add_vbo(mesh->vao, tvbo);
    mesh->vao->bind_ibo(mesh->vao, ibo);

    return mesh;
}