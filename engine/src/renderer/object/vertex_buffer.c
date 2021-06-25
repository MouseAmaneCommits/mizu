#include "vertex_buffer.h"

#include "../renderer.h"

#include "../object/opengl/ogl_vertex_buffer.h"

void m_init_vertex_buffer(m_vertex_buffer* vbo, float* vertices, u32 size){
    switch(m_renderer_get_api()){
        case OPENGL:
            m_init_vertex_buffer_opengl(vbo, vertices, size);
            break;
    }
}

void m_destory_vertex_buffer(m_vertex_buffer* vbo){
    switch(m_renderer_get_api()){
        case OPENGL:
            m_destroy_vertex_buffer_opengl(vbo);
            break;
    }
}