#include "application.h"

#include "../renderer/renderer.h"

#include <sys/time.h>
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
        // struct timeval start, stop; 
        // double milli = 0;
        // gettimeofday(&start, NULL);
        
        m_update_platform(&self->platform);

        m_begin_frame();
        
        for(u32 i = 0; i < self->layer_index; i++){
            self->layers[i]->update();
        }
        

        m_end_frame();

        // gettimeofday(&stop, NULL);
        // milli = (double)((stop.tv_usec - start.tv_usec) / 1000) + ((stop.tv_sec - start.tv_sec) * 1000);
        // printf("game loop iteration(elapsed ms): %f\n",milli);
    }

    for(u32 i = 0; i < self->layer_index; i++){
        self->layers[i]->detach();
    }

    m_destroy_platform(&self->platform);
}