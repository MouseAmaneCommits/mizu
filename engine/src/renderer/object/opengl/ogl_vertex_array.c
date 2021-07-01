#include "ogl_vertex_array.h"

#define UNIMPLEMENTED_DATA_SIZE 6553

#include "../../../memory/mmemory.h"
#include <time.h>
#include <glad/glad.h>
#include <malloc.h>
#include <memory.h>
#include <sys/time.h>

#include "ogl_vertex_buffer.h"
#include "../../../core/logger.h"

typedef struct {
    u32 id;
}internal_memory;

static void ogl_bind(m_vertex_array* self){
    glBindVertexArray(((internal_memory*)(self->unimplemented_data))->id);
}

static void ogl_unbind(m_vertex_array* self){
    glBindVertexArray(0);
}

static void ogl_add_vbo(m_vertex_array* self, m_vertex_buffer* buffer){
    if(self->vbo_index < MAX_VBO_COUNT){
        ogl_bind(self);
        buffer->bind(buffer);
        glEnableVertexAttribArray(buffer->layout.index);
        glVertexAttribPointer(buffer->layout.index, buffer->layout.size, GL_FLOAT, GL_FALSE, 0, (const void*)0);
        glDisableVertexAttribArray(buffer->layout.index);
        buffer->unbind(buffer);
        ogl_unbind(self);

        self->vbos[self->vbo_index] = buffer;
        self->vbo_index++;
    }else{
        M_ERROR("Cannot add more vbos to vao, than the max vbo count!");
    }
}

static void ogl_draw(m_vertex_array* self){
    ogl_bind(self);
    for(u32 i = 0; i < self->vbo_index; i++){
        glEnableVertexAttribArray(self->vbos[i]->layout.index);
    }
    
    if(!self->ibo_bound){
        if(self->o_primitive_type != PRIMITIVE_QUADS)
            glDrawArrays(GL_TRIANGLES, 0, self->vbos[0]->length/3);
        else
            glDrawArrays(GL_QUADS, 0, self->vbos[0]->length/3); 
    }
    else{
        self->ibo->bind(self->ibo);
        if(self->o_primitive_type != PRIMITIVE_QUADS)
            glDrawElements(GL_TRIANGLES, self->ibo->count, GL_UNSIGNED_INT, NULL);
        else
            glDrawElements(GL_QUADS, self->ibo->count, GL_UNSIGNED_INT, NULL);
        self->ibo->unbind(self->ibo);
    }

    for(u32 i = 0; i < self->vbo_index; i++){
        glDisableVertexAttribArray(self->vbos[i]->layout.index);
    }

    ogl_unbind(self);


}

static void ogl_bind_ibo(m_vertex_array* self, m_index_buffer* ibo){
    self->ibo_bound = TRUE;
    self->ibo = ibo;
}

void m_init_vertex_array_opengl(m_vertex_array* array){
    array->ibo_bound = FALSE;
    
    array->unimplemented_data = QUICK_MALLOC(internal_memory);

    u32 id = 0;
    glGenVertexArrays(1, &id);
    ((internal_memory*)(array->unimplemented_data))->id = id;

    array->bind = ogl_bind;
    array->unbind = ogl_unbind;
    array->add_vbo = ogl_add_vbo;
    array->draw = ogl_draw;
    array->bind_ibo = ogl_bind_ibo;
}

void m_destroy_vertex_array_opengl(m_vertex_array* self){
    for(u32 i = 0; i < self->vbo_index; i++){
        m_destroy_vertex_buffer_opengl(self->vbos[i]);
        free(self->vbos[i]);
    }

    glDeleteVertexArrays(1, ((internal_memory*)(self->unimplemented_data)));
    
    free(self->unimplemented_data);
}