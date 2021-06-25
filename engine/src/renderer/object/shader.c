#include "shader.h"
#include "../renderer.h"
#include "../object/opengl/ogl_shader.h"

void m_init_shader(m_shader* shader, const char* vertex_shader_name, const char* fragment_shader_name){
    switch(m_renderer_get_api()){
        case OPENGL:
            m_init_shader_opengl(shader, vertex_shader_name, fragment_shader_name);
            break;
    }
}

void m_destroy_shader(m_shader* shader){
    switch(m_renderer_get_api()){
        case OPENGL:
            m_destroy_shader_opengl(shader);
            break;
    }
}