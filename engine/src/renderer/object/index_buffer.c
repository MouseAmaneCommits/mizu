#include "index_buffer.h"
#include "../object/opengl/ogl_index_buffer.h"
#include "../renderer.h"

void m_init_index_buffer(m_index_buffer* ibo, u32* indices, u32 size){
    switch(m_renderer_get_api()){
        case OPENGL:
            m_init_index_buffer_opengl(ibo, indices, size);
            break;
    }
}

void m_destroy_index_buffer(m_index_buffer* ibo){
    switch(m_renderer_get_api()){
        case OPENGL:
            m_destroy_index_buffer_opengl(ibo);
            break;
    }
}