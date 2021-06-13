#include "renderer.h"
#include "context/context.h"
#include "context/api/opengl_context.h"

#include <malloc.h>
#include <memory.h>

static m_context* context;


void m_init_renderer(m_platform* platform, m_renderer_api api){
    context = (m_context*)malloc(sizeof(m_context));
    memset(context, 0, sizeof(m_context));

    m_init_context(context, platform, api);
    context->init();
}

void m_begin_frame(){
    context->begin_frame();
}

void m_end_frame(){
    context->end_frame();
}