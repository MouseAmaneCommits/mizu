#include "../../engine/src/core/application.h"
#include "../../engine/src/core/logger.h"
#include "../../engine/src/renderer/object/opengl/ogl_vertex_array.h"
#include "../../engine/src/renderer/object/opengl/ogl_vertex_buffer.h"
#include "../../engine/src/renderer/object/opengl/ogl_index_buffer.h"
#include "../../engine/src/renderer/object/opengl/ogl_shader.h"
#include "../../engine/src/renderer/object/opengl/ogl_texture.h"
#include "../../engine/src/renderer/renderer.h"
#include "../../engine/src/mesh/mesh.h"
#include <malloc.h>
#include <memory.h>

#include <windows.h>
#include <sys/time.h>
#include <glad/glad.h>

f32 vertices[] = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f 
};
f32 texture_coords[] = {
    // texture coords
    1.0f, 1.0f,   // top right
    1.0f, 0.0f,   // bottom ri
    0.0f, 0.0f,   // bottom le
    0.0f, 1.0f    // top left 
};

u32 indices[] = {
    0, 1, 3,   
    1, 2, 3    
};  




    const static f32 vertices_cube[] =
    {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };

    const static f32 texture_coords_cube[] =
    {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
    };

static m_camera* camera;
static m_mesh* mesh;

// void init_other_vao(){
//     m_vertex_buffer_layout layout;
//     layout.index = 0;
//     layout.size = 3;

//     m_init_vertex_array(&other_test);

//     m_vertex_buffer* buf = QUICK_MALLOC(m_vertex_buffer);
//     memset(buf, 0, sizeof(m_vertex_buffer));
//     m_init_vertex_buffer(buf, vertices, sizeof(vertices));
//     buf->set_layout(buf, &layout);

//     layout.index = 1;
//     layout.size = 2;

//     m_vertex_buffer* tbuf = QUICK_MALLOC(m_vertex_buffer);
//     memset(tbuf, 0, sizeof(m_vertex_buffer));
//     m_init_vertex_buffer(tbuf, texture_coords, sizeof(texture_coords));
//     tbuf->set_layout(tbuf, &layout);
    
//     m_index_buffer* ibo = QUICK_MALLOC(m_index_buffer);
//     memset(ibo, 0, sizeof(m_index_buffer));
//     m_init_index_buffer(ibo, indices, sizeof(indices));

//     other_test.add_vbo(&other_test, buf);
//     other_test.add_vbo(&other_test, tbuf);
//     other_test.bind_ibo(&other_test, ibo);

//     m_init_shader(&shader_other_test, "vertex_shader.vs.glsl", "fragment_shader.fs.glsl");
// }

void fl_start(){
    camera = QUICK_MALLOC(m_camera);
    memset(camera, 0, sizeof(m_camera));
    camera->view = m_identity_matrix();
    camera->proj = m_perspective(1280/720, to_radians(10), from_radians(0.1f), from_radians(1000.0f));
    camera->o_clear_color[0] = 0.0f; camera->o_clear_color[1] = 0.5f; camera->o_clear_color[2] = 1.0f; camera->o_clear_color[3] = 0.0f;
    m_bind_camera(camera);

    m_properties* properties = QUICK_MALLOC(m_properties);
    memset(properties, 0, sizeof(m_properties));
    properties->pos = m_init_vec3(0, 0, 0);
    properties->sca = m_init_vec3(1, 1, 1);
    

    CREATE(m_texture, m_init_texture(texture, 0, "angel.jpg"), texture);
    properties->material = QUICK_MALLOC(m_material);
    properties->material->t_albedo = texture;
    mesh = m_create_plane(properties);
}

void fl_update(){
    if(GetAsyncKeyState('S')){
        m_translate_camera(camera, m_init_vec3(0, 0, -0.1f));
    }
    if(GetAsyncKeyState('W')){
        m_translate_camera(camera, m_init_vec3(0, 0, 0.1f));
    }
    if(GetAsyncKeyState('D')){
        m_translate_camera(camera, m_init_vec3(-0.1f, 0, 0));
    }
    if(GetAsyncKeyState('A')){
       m_translate_camera(camera, m_init_vec3(0.1f, 0, 0));
    }

    m_rotate_matrix(&mesh->model, m_init_vec3(0.01, 0, 0));

    mesh->draw(mesh);
}

void fl_stop(){
    
}

int main(int argc, char const *argv[])
{
    m_application game;
    m_init_application(&game);

    m_layer layer = {0};
    layer.attach = fl_start;
    layer.update = fl_update;
    layer.detach = fl_stop;

    m_push_application_layer(&game, &layer);

    m_run_application(&game, 1920/6, 1080/6, 1280, 720, "mizu");

    return 0;
}