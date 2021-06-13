#include "application.h"

#include "../renderer/renderer.h"

#include <malloc.h>

void m_init_application(m_application* self){
    self->layer_index = 0;
}

void m_push_application_layer(m_application* self, m_layer* layer){
    if(self->layer_index < MAX_LAYER_COUNT){
        self->layers[self->layer_index] = layer;
        self->layer_index++;
    }
}

void m_run_application(m_application* self, u32 x, u32 y, u32 width, u32 height, const char* title){
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;
    self->title = title;

    //self->platform = (m_platform*)malloc(sizeof(m_platform));
    m_init_platform(&self->platform, self->x, self->y, self->width, self->height, self->title);

    m_init_renderer(&self->platform, OPENGL);
    
    for(u32 i = 0; i < self->layer_index; i++){
        self->layers[i]->attach();
    }

    while(!m_closing_platform(&self->platform)){
        m_begin_frame();
        for(u32 i = 0; i < self->layer_index; i++){
            self->layers[i]->update();
        }
        
        m_update_platform(&self->platform);

        m_end_frame();
    }

    for(u32 i = 0; i < self->layer_index; i++){
        self->layers[i]->detach();
    }
}