#include "vertex_array.h"

#include "../renderer.h"

#include "../object/opengl/ogl_vertex_array.h"

void m_init_vertex_array(m_vertex_array* vao){
    switch(m_renderer_get_api()){
        case OPENGL:
            m_init_vertex_array_opengl(vao);
            break;
    }
}