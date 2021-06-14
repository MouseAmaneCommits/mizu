#include <stdio.h>
#include "../../engine/src/core/application.h"
#include "../../engine/src/core/logger.h"
#include "../../engine/src/renderer/object/opengl/ogl_vertex_array.h"
#include "../../engine/src/renderer/object/opengl/ogl_vertex_buffer.h"
#include "../../engine/src/renderer/object/opengl/ogl_shader.h"

#include <glad/glad.h>

static float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

static m_shader shader;
static m_vertex_buffer vbo;
static m_vertex_array array;
static m_vertex_buffer_layout layout;
static mat4 view;
static mat4 proj;

void fl_start(){
    view = m_identity_matrix();
    // print_list(m_convert_matrix_to_float_array(view));
    proj = m_identity_matrix();

    layout.index = 0;
    layout.size = 3;

    m_init_vertex_array_opengl(&array);
    m_init_vertex_buffer_opengl(&vbo, vertices, sizeof(vertices));
    vbo.set_layout(&vbo, &layout);

    array.add_vbo(&array, &vbo);

    m_init_shader_opengl(&shader, "vertex_shader.vs.glsl", "fragment_shader.fs.glsl");
}

void fl_update(){
    shader.bind(&shader);
    m_translate_matrix(&view, m_init_vec3(0.01f, 0.0f, 0.0f));
    shader.set_mat4(&shader, "view", view);
    shader.set_mat4(&shader, "proj", proj);
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
