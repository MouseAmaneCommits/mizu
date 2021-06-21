#include "renderer.h"
#include "context/context.h"
#include "context/api/opengl_context.h"

#include "../memory/mmemory.h"
#include <malloc.h>
#include <memory.h>
#include "../core/logger.h"

static m_context* context;
static b8 initialized = FALSE;
static m_camera* camera;
static m_render_queue* render_queue;

static void init_render_queue(m_render_queue* queue){
    queue->location = 0;
    queue->num_elements = 0;
}

static void append_to_render_queue(m_render_queue* queue){
    
}

void m_init_renderer(m_platform* platform, m_renderer_api api){
    context = (m_context*)malloc(sizeof(m_context));
    memset(context, 0, sizeof(m_context));

    m_init_context(context, platform, api);
    context->init();
    initialized = TRUE;
}

void m_begin_frame(){
    context->begin_frame();
}

void m_bind_camera(m_camera* cam){
    M_INFO("Binding camera...");
    camera = cam;
}

void m_submit(m_vertex_array* array, m_shader* shader, m_camera* camera, mat4* model){
    shader->bind(shader);

    // Set all uniforms
    shader->set_mat4(shader, "model", *model);
    shader->set_mat4(shader, "view", camera->view);
    shader->set_mat4(shader, "proj", camera->proj);
    // Its render time!
    array->draw(array);


    shader->unbind(shader);
}

void m_end_frame(){
    context->end_frame();
}

void m_reshape_renderer(u32 width, u32 height){
    context->reshape(width, height);
}

b8 m_initialized_renderer(){
    return initialized;
}

m_renderer_api m_renderer_get_api(){
    return context->api;
}