#include "../../engine/src/core/application.h"
#include "../../engine/src/core/logger.h"
#include "../../engine/src/renderer/object/opengl/ogl_vertex_array.h"
#include "../../engine/src/renderer/object/opengl/ogl_vertex_buffer.h"
#include "../../engine/src/renderer/object/opengl/ogl_index_buffer.h"
#include "../../engine/src/renderer/object/opengl/ogl_shader.h"
#include "../../engine/src/renderer/object/opengl/ogl_texture.h"
#include "../../engine/src/renderer/renderer.h"
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

static m_camera* camera;
static m_vertex_array test; static m_shader shader_test; static mat4 test_model;
static m_vertex_array other_test;
static m_shader shader_other_test;

void init_vao(){
    test_model = m_identity_matrix();

    m_vertex_buffer_layout layout;
    layout.index = 0;
    layout.size = 3;

    m_init_vertex_array(&test);

    m_vertex_buffer* buf = QUICK_MALLOC(m_vertex_buffer);
    memset(buf, 0, sizeof(m_vertex_buffer));
    m_init_vertex_buffer(buf, vertices, sizeof(vertices));
    buf->set_layout(buf, &layout);

    layout.index = 1;
    layout.size = 2;

    m_vertex_buffer* tbuf = QUICK_MALLOC(m_vertex_buffer);
    memset(tbuf, 0, sizeof(m_vertex_buffer));
    m_init_vertex_buffer(tbuf, texture_coords, sizeof(texture_coords));
    tbuf->set_layout(tbuf, &layout);
    
    m_index_buffer* ibo = QUICK_MALLOC(m_index_buffer);
    memset(ibo, 0, sizeof(m_index_buffer));
    m_init_index_buffer(ibo, indices, sizeof(indices));

    test.add_vbo(&test, buf);
    test.add_vbo(&test, tbuf);
    test.bind_ibo(&test, ibo);
}

void init_other_vao(){
    m_vertex_buffer_layout layout;
    layout.index = 0;
    layout.size = 3;

    m_init_vertex_array(&other_test);

    m_vertex_buffer* buf = QUICK_MALLOC(m_vertex_buffer);
    memset(buf, 0, sizeof(m_vertex_buffer));
    m_init_vertex_buffer(buf, vertices, sizeof(vertices));
    buf->set_layout(buf, &layout);

    layout.index = 1;
    layout.size = 2;

    m_vertex_buffer* tbuf = QUICK_MALLOC(m_vertex_buffer);
    memset(tbuf, 0, sizeof(m_vertex_buffer));
    m_init_vertex_buffer(tbuf, texture_coords, sizeof(texture_coords));
    tbuf->set_layout(tbuf, &layout);
    
    m_index_buffer* ibo = QUICK_MALLOC(m_index_buffer);
    memset(ibo, 0, sizeof(m_index_buffer));
    m_init_index_buffer(ibo, indices, sizeof(indices));

    other_test.add_vbo(&other_test, buf);
    other_test.add_vbo(&other_test, tbuf);
    other_test.bind_ibo(&other_test, ibo);

    m_init_shader(&shader_test, "vertex_shader.vs.glsl", "fragment_shader.fs.glsl");
}

void fl_start(){
    init_vao();
    init_other_vao();

    camera = (m_camera*)malloc(sizeof(m_camera));
    memset(camera, 0, sizeof(m_camera));
    camera->view = m_identity_matrix();
    camera->proj = m_orthographic(-1, 1, -1, 1, 0.01f, 1000.0f);
    m_bind_camera(camera);
}

void fl_update(){
    m_submit(&test, &shader_test, &test_model);
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