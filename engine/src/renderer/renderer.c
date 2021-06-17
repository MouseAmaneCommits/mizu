#include "renderer.h"
#include "context/context.h"
#include "context/api/opengl_context.h"

#include "../memory/mmemory.h"
#include <malloc.h>
#include <memory.h>

static m_context* context;
static b8 initialized = FALSE;


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