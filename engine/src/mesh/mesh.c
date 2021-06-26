#include "mesh.h"

#include <memory.h>
#include <malloc.h>

#include "../renderer/renderer.h"
#include "../core/logger.h"
#include "../utils/array.h"

#include <stdio.h>
#include <stdlib.h>

#define FAST_OBJ_IMPLEMENTATION
#include "fastobj.h"

static void mesh_draw(m_mesh* mesh){
    if(mesh->material->t_albedo == NULL)
        m_submit(mesh->vao, mesh->shader, &mesh->model);
    else
        m_submit_with_texture(mesh->vao, mesh->shader, mesh->material->t_albedo, &mesh->model);
}

m_mesh* m_load_from_file(const char* filename, m_properties* properties){
    // allocations
    m_mesh* mesh = QUICK_MALLOC(m_mesh);
    memset(mesh, 0, sizeof(m_mesh));
    mesh->vao = QUICK_MALLOC(m_vertex_array);
    memset(mesh->vao, 0, sizeof(m_vertex_array));
    mesh->shader = QUICK_MALLOC(m_shader);
    memset(mesh->shader, 0, sizeof(m_shader));


    fastObjMesh* fast_obj_mesh = fast_obj_read(filename);
    

    u32 vertices_length = ((-1 + fast_obj_mesh->position_count)*3);
    printf("%i\n", vertices_length);
    f32* temp_vertices = fast_obj_mesh->positions;
    f32* vertices = malloc(vertices_length * sizeof(float));

    u32 indices_length = fast_obj_mesh->face_count * 3;
    u32* indices = malloc(sizeof(u32) * indices_length); 

    u32 texture_coords_length = fast_obj_mesh->texcoord_count;
    f32* texture_coords = fast_obj_mesh->texcoords;
    
    for(u32 i = 0; i < vertices_length; i += 3){
        vertices[i] = temp_vertices[i+3];
        vertices[i+1] = temp_vertices[i+3+1];
        vertices[i+2] = temp_vertices[i+3+2];
    }

    for(u32 i = 0; i < indices_length; i+=1){
        indices[i] = fast_obj_mesh->indices[i].p-1;
    }

    m_vertex_buffer_layout layout;
    layout.index = 0;
    layout.size = 3;

    // initializations
    mesh->draw = mesh_draw;

    m_init_vertex_array(mesh->vao);
    m_init_shader(mesh->shader, "vertex_shader.vs.glsl", "fragment_shader.fs.glsl");
    CREATE(m_vertex_buffer, m_init_vertex_buffer(vbo, vertices, vertices_length * sizeof(float)), vbo);
    vbo->set_layout(vbo, &layout);
    CREATE(m_vertex_buffer, m_init_vertex_buffer(tvbo, texture_coords, texture_coords_length * sizeof(float)), tvbo);
    layout.index = 1; layout.size = 2;
    tvbo->set_layout(tvbo, &layout);
    CREATE(m_index_buffer, m_init_index_buffer(ibo, indices, indices_length * sizeof(u32)), ibo);
    mesh->vao->add_vbo(mesh->vao, vbo);
    mesh->vao->add_vbo(mesh->vao, tvbo);
    mesh->vao->bind_ibo(mesh->vao, ibo);

    mesh->material = QUICK_MALLOC(m_material);
    memcpy(mesh->material, properties->material, sizeof(m_material));

    mesh->model = m_identity_matrix();
    m_translate_matrix(&mesh->model, properties->pos);
    m_scale_matrix_vec3(&mesh->model, properties->sca);

    return mesh;
}

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
    mesh->draw = mesh_draw;

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

    mesh->material = QUICK_MALLOC(m_material);
    memcpy(mesh->material, properties->material, sizeof(m_material));

    mesh->model = m_identity_matrix();
    m_translate_matrix(&mesh->model, properties->pos);
    m_scale_matrix_vec3(&mesh->model, properties->sca);

    return mesh;
}