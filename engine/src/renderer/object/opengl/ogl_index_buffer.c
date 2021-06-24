#include "ogl_index_buffer.h"

#include "../../../memory/mmemory.h"
#include <malloc.h>
#include <memory.h>
#include <glad/glad.h>

#define UNIMPLEMENTED_DATA_SIZE 6553

typedef struct {
    u32 id;
}internal_memory;

static void ogl_bind(m_index_buffer* self){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ((internal_memory*)self->unimplemented_data)->id);
}

static void ogl_unbind(m_index_buffer* self){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

static void ogl_init(m_index_buffer* self, u32* indices, u32 size){
    u32 id = 0;
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    ((internal_memory*)self->unimplemented_data)->id = id;
}

void m_init_index_buffer_opengl(m_index_buffer* self, u32* indices, u32 size){
    self->unimplemented_data = QUICK_MALLOC(internal_memory);
    self->count = size / sizeof(u32); 

    ogl_init(self, indices, size);
    
    
    self->bind = ogl_bind;
    self->unbind = ogl_unbind;
}

void m_destroy_index_buffer_opengl(m_index_buffer* self){
    glDeleteBuffers(1, &((internal_memory*)self->unimplemented_data)->id);

    free(self->unimplemented_data);
}