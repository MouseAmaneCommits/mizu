#include "context.h"

#include "api/opengl_context.h"

void m_init_context(m_context* context, m_platform* platform, m_renderer_api api){
    context->platform = platform;
    switch(api){
        case OPENGL: {
            m_init_context_ogl(context);
            break;
        }
    }
}