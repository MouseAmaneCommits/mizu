#include "ogl_uniform_buffer.h"

#include <malloc.h>
#include <memory.h>

#include <glad\glad.h>

#define UNIMPLEMENTED_DATA_SIZE 6553

typedef struct {
    u32 id;
}internal_memory;

static void ogl_bind(m_uniform_buffer* self){
    internal_memory* memory = (internal_memory*)self->unimplemented_data;
    glBindBuffer(GL_UNIFORM_BUFFER, memory->id);
}

static void ogl_unbind(m_uniform_buffer* self){
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

static void ogl_init(m_uniform_buffer* self, u32 buffer_size){
    internal_memory* memory = (internal_memory*)(self->unimplemented_data);
    glGenBuffers(1, &memory->id);

    glBindBuffer(GL_UNIFORM_BUFFER, memory->id);
    glBufferData(GL_UNIFORM_BUFFER, buffer_size, 0, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void m_init_uniform_buffer_opengl(m_uniform_buffer* buffer, const char* name, u32 buffer_size){
    buffer->unimplemented_data = QUICK_MALLOC(internal_memory);
    buffer->name = name;

    ogl_init(buffer, buffer_size);

    buffer->bind = ogl_bind;
    buffer->unbind = ogl_unbind;
}