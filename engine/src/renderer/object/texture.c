#include "texture.h"
#include "../renderer.h"
#include "../object/opengl/ogl_texture.h"

void m_init_texture(m_texture* texture, u32 bind_slot, const char* filename){
    switch(m_renderer_get_api()){
        case OPENGL:
            m_init_texture_opengl(texture, bind_slot, filename);
            break;
    }
}