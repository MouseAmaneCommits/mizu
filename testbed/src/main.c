#include <stdio.h>
#include "../../engine/src/core/application.h"
#include "../../engine/src/core/logger.h"
#include "../../engine/src/renderer/object/opengl/ogl_vertex_array.h"
#include "../../engine/src/renderer/object/opengl/ogl_vertex_buffer.h"
#include "../../engine/src/renderer/object/opengl/ogl_index_buffer.h"
#include "../../engine/src/renderer/object/opengl/ogl_shader.h"
#include "../../engine/src/renderer/object/opengl/ogl_texture.h"


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

static float texCoords[] = {
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

static m_shader shader;
static m_vertex_buffer vbo;
static m_vertex_buffer tbo;
static m_index_buffer ibo;
static m_vertex_array array;
static m_vertex_buffer_layout layout;
static m_vertex_buffer_layout tlayout;
static m_texture texture;

static mat4 view;
static mat4 proj;
static mat4 model;

void fl_start(){
    view = m_identity_matrix();
    // print_list(m_convert_matrix_to_float_array(view));
    proj = m_orthographic(-1, 1, -1, 1, 0.01f, 1000.0f);
    //proj = m_identity_matrix();

    model = m_identity_matrix();

    layout.index = 0;
    layout.size = 3;

    m_init_vertex_array_opengl(&array);
    m_init_vertex_buffer_opengl(&vbo, vertices, sizeof(vertices));
    vbo.set_layout(&vbo, &layout);

    array.add_vbo(&array, &vbo);

    m_init_vertex_buffer_opengl(&tbo, texCoords, sizeof(texCoords));
    tlayout.index = 1;
    tlayout.size = 2;
    tbo.set_layout(&tbo, &tlayout);
    array.add_vbo(&array, &tbo);

    m_init_texture_opengl(&texture, 0, "brik.png");
    
    // m_init_index_buffer_opengl(&ibo, indices, sizeof(indices));
    // array.bind_ibo(&array, &ibo);
    

    m_init_shader_opengl(&shader, "vertex_shader.vs.glsl", "fragment_shader.fs.glsl");

    // m_translate_matrix(&view, m_init_vec3(0, 0, -1));
}

void fl_update(){
    // m_translate_matrix(&model, m_init_vec3(0.1f, 0, 0));

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

    texture.bind(&texture);
    shader.bind(&shader);
    shader.set_int(&shader, "tex", 0);
    shader.set_mat4(&shader, "view", view);
    shader.set_mat4(&shader, "proj", proj);
    shader.set_mat4(&shader, "model", model);
    array.draw(&array);
    shader.unbind(&shader);
    texture.unbind(&texture);
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
