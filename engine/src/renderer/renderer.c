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
    queue->capacity = 1000;
    queue->front = queue->size = 0;
    queue->rear = queue->capacity-1;
}

static b8 is_render_queue_full(m_render_queue* queue){
    return (queue->size == queue->capacity);
}

static b8 is_render_queue_empty(m_render_queue* queue){
    return (queue->size == 0);
}

static void append_to_render_queue(m_render_queue* queue, m_package* package){
    if(is_render_queue_full(queue)){
        M_WARN("Too many packets sent to the renderer! Ignored other packets...");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->packages[queue->rear] = package;
    queue->size++;
}

static m_package* dequeue_render_queue(m_render_queue* queue){
    if(is_render_queue_empty(queue)){
        M_ERROR("Render queue empty, cannot dequeue!");
        return NULL;
    }
    m_package* pck = queue->packages[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return pck;
}

static m_package* front_render_queue(m_render_queue* queue){
    if(is_render_queue_empty(queue)){
        M_ERROR("Render queue empty, cannot acquire front of render queue!");
        return NULL;
    }
    return queue->packages[queue->front];
}

static m_package* rear_render_queue(m_render_queue* queue){
    if(is_render_queue_empty(queue)){
        M_ERROR("Render queue empty, cannot acquire front of render queue!");
        return NULL;
    }
    return queue->packages[queue->rear];
}

void m_init_renderer(m_platform* platform, m_renderer_api api){
    render_queue = QUICK_MALLOC(m_render_queue);
    memset(render_queue, 0, sizeof(m_render_queue));
    init_render_queue(render_queue);

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

    for(u32 i = 0; i < render_queue->size; i++){
        m_package* package = dequeue_render_queue(render_queue);
        
        package->shader->bind(package->shader);

        // Set all uniforms
        package->shader->set_mat4(package->shader, "model", *package->model);
        package->shader->set_mat4(package->shader, "view", camera->view);
        package->shader->set_mat4(package->shader, "proj", camera->proj);
        // Its render time!
        package->array->draw(package->array);

        package->shader->unbind(package->shader);
        free(package);
    }

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