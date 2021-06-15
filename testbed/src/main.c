#include <stdio.h>
#include "../../engine/src/core/application.h"
#include "../../engine/src/core/logger.h"
#include "../../engine/src/renderer/object/opengl/ogl_vertex_array.h"
#include "../../engine/src/renderer/object/opengl/ogl_vertex_buffer.h"
#include "../../engine/src/renderer/object/opengl/ogl_index_buffer.h"
#include "../../engine/src/renderer/object/opengl/ogl_shader.h"


#include <windows.h>
#include <sys/time.h>
#include <glad/glad.h>

// static float vertices[] = {
//      0.5f,  0.5f, 0.0f,  // top right
//      0.5f, -0.5f, 0.0f,  // bottom right
//     -0.5f, -0.5f, 0.0f,  // bottom left
//     -0.5f,  0.5f, 0.0f   // top left 
// };

// static u32 indices[] = {
//     0, 1, 3,   // first triangle
//     1, 2, 3    // second triangle
// };

static float vertices[] = {
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

static m_shader shader;
static m_vertex_buffer vbo;
static m_index_buffer ibo;
static m_vertex_array array;
static m_vertex_buffer_layout layout;
static mat4 view;
static mat4 proj;
static mat4 model;

void fl_start(){
    view = m_identity_matrix();
    // print_list(m_convert_matrix_to_float_array(view));
    proj = m_orthographic(-1, 1, -1, 1, 0.01f, 1000.0f);

    model = m_identity_matrix();

    layout.index = 0;
    layout.size = 3;

    m_init_vertex_array_opengl(&array);
    m_init_vertex_buffer_opengl(&vbo, vertices, sizeof(vertices));
    vbo.set_layout(&vbo, &layout);

    array.add_vbo(&array, &vbo);
    
    // m_init_index_buffer_opengl(&ibo, indices, sizeof(indices));
    // array.bind_ibo(&array, &ibo);
    

    m_init_shader_opengl(&shader, "vertex_shader.vs.glsl", "fragment_shader.fs.glsl");

    m_translate_matrix(&view, m_init_vec3(0, 0, -1));
}

void fl_update(){
    //m_translate_matrix(&model, m_init_vec3(0.1f, 0, 0));

    if(GetAsyncKeyState('D')){
        m_translate_matrix(&view, m_init_vec3(-0.1f, 0, 0));
    }
    if(GetAsyncKeyState('A')){
        m_translate_matrix(&view, m_init_vec3(0.1f, 0, 0));
    }
    if(GetAsyncKeyState('S')){
        m_translate_matrix(&view, m_init_vec3(0, 0, -0.1f));
    }
    if(GetAsyncKeyState('W')){
        m_translate_matrix(&view, m_init_vec3(0, 0, 0.1f));
    }

    if(GetAsyncKeyState('E')){
        m_rotate_matrix(&model, m_init_vec3(0, 0, 0.1f));
    }
    if(GetAsyncKeyState('Q')){
        m_rotate_matrix(&model, m_init_vec3(0, 0, -0.1f));
    }

    if(GetAsyncKeyState('C')){
        m_rotate_matrix(&view, m_init_vec3(0, -0.1f, 0));
    }
    if(GetAsyncKeyState('Z')){
        m_rotate_matrix(&view, m_init_vec3(0, 0.1f, 0));
    }


    shader.bind(&shader);
    shader.set_mat4(&shader, "view", view);
    shader.set_mat4(&shader, "proj", proj);
    shader.set_mat4(&shader, "model", model);
    array.draw(&array);
    shader.unbind(&shader);
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
