#include "renderer.h"
#include "context/context.h"
#include "context/api/opengl_context.h"

#include "../memory/mmemory.h"
#include <malloc.h>
#include <memory.h>
#include "../core/logger.h"
#include "../performance/performance.h"

static m_context* context;
static b8 initialized = FALSE;
static m_camera* camera;
static m_render_queue* render_queue;

static void init_render_queue(m_render_queue* queue){
    queue->location = 0;
}

static void append_to_render_queue(m_render_queue* queue, m_package* package){
    if(queue->location < INITIAL_TOTAL_PACKAGE_SIZE){
        queue->packages[queue->location] = package;
        queue->location++;
    }else{
        M_WARN("Too many packets sent to the renderer! Ignored other packets...");
    }
}

static void clear_render_queue(m_render_queue* queue){
    queue->location = 0;
}

void m_init_renderer(m_platform* platform, m_renderer_api api){
    render_queue = QUICK_MALLOC(m_render_queue);
    memset(render_queue, 0, sizeof(m_render_queue));

    context = QUICK_MALLOC(m_context);
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

void m_submit(m_vertex_array* array, m_shader* shader, mat4* model){
    if(array->bind == NULL || shader->bind == NULL){ // test to see, if one of the functions is initialized, since you can't really say if(struct == NULL), cuz thats not a thing in c
        M_ERROR("Shader or Array cannot be NULL!");
    }

    m_package* render_package = QUICK_MALLOC(m_package);
    memset(render_package, 0, sizeof(m_package));
    render_package->array = array;
    render_package->shader = shader;
    render_package->model = model;
    append_to_render_queue(render_queue, render_package);
}

void m_flush(){
    time_it_begin();
    for(u32 i = 0; i < render_queue->location; i++){
        render_queue->packages[i]->shader->bind(render_queue->packages[i]->shader);

        // Set all uniforms
        render_queue->packages[i]->shader->set_mat4(render_queue->packages[i]->shader, "model", *render_queue->packages[i]->model);
        render_queue->packages[i]->shader->set_mat4(render_queue->packages[i]->shader, "view", camera->view);
        render_queue->packages[i]->shader->set_mat4(render_queue->packages[i]->shader, "proj", camera->proj);
        // Its render time!
        render_queue->packages[i]->array->draw(render_queue->packages[i]->array);

        render_queue->packages[i]->shader->unbind(render_queue->packages[i]->shader);
        free(render_queue->packages[i]);
    }

    clear_render_queue(render_queue);
    time_it_end();

    M_INFO("Elapsed time (renderer-flush) %f", time_get_elapsed());
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