#include "ogl_vertex_array.h"

#define UNIMPLEMENTED_DATA_SIZE 6553

#include <time.h>
#include <glad/glad.h>
#include <malloc.h>
#include <memory.h>
#include <sys/time.h>

#include "../../../core/logger.h"

static void ogl_bind(m_vertex_array* self){
    u32 id = 0;
    memcpy(&id, self->unimplemented_data, sizeof(u32));
    glBindVertexArray(id);
}

static void ogl_unbind(m_vertex_array* self){
    glBindVertexArray(0);
}

static void ogl_add_vbo(m_vertex_array* self, m_vertex_buffer* buffer){
    if(self->vbo_index < MAX_VBO_COUNT){
        ogl_bind(self);
        buffer->bind(buffer);
        glEnableVertexAttribArray(buffer->layout->index);
        glVertexAttribPointer(buffer->layout->index, buffer->layout->size, GL_FLOAT, GL_FALSE, 0, (const void*)0);
        glDisableVertexAttribArray(buffer->layout->index);
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
    glEnableVertexAttribArray(self->vbos[0]->layout->index);
    
    if(!self->ibo_bound){
        glDrawArrays(GL_TRIANGLES, 0, self->vbos[0]->length/3);
    }
    else{
        self->ibo->bind(self->ibo);
        glDrawElements(GL_TRIANGLES, self->ibo->count, GL_UNSIGNED_INT, NULL);
        self->ibo->unbind(self->ibo);
    }

    glDisableVertexAttribArray(self->vbos[0]->layout->index);
    ogl_unbind(self);


}

static void ogl_bind_ibo(m_vertex_array* self, m_index_buffer* ibo){
    self->ibo_bound = TRUE;
    self->ibo = ibo;
}

void m_init_vertex_array_opengl(m_vertex_array* array){
    array->ibo_bound = FALSE;
    
    array->unimplemented_data = malloc(UNIMPLEMENTED_DATA_SIZE);
    u32 id = 0;
    glGenVertexArrays(1, &id);
    memcpy(array->unimplemented_data, &id, sizeof(u32));

    array->bind = ogl_bind;
    array->unbind = ogl_unbind;
    array->add_vbo = ogl_add_vbo;
    array->draw = ogl_draw;
    array->bind_ibo = ogl_bind_ibo;
}