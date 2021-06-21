#include "ogl_vertex_buffer.h"

#include <memory.h>
#include <malloc.h>
#include <glad/glad.h>
#include "../../../memory/mmemory.h"

#define UNIMPLEMENTED_DATA_SIZE 6553

static void ogl_bind(m_vertex_buffer* self){
    u32 id = 0;
    memcpy(&id, self->unimplemented_data, sizeof(u32));
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

static void ogl_unbind(m_vertex_buffer* self){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void ogl_set_layout(m_vertex_buffer* self, m_vertex_buffer_layout* layout){
    self->layout.index = layout->index;
    self->layout.size = layout->size;
}

void m_init_vertex_buffer_opengl(m_vertex_buffer* self, float* vertices, u32 size_of_vertices){
    self->unimplemented_data = malloc(UNIMPLEMENTED_DATA_SIZE);

    u32 id = 0;
    glGenBuffers(1, &id);
    memcpy(self->unimplemented_data, &id, sizeof(u32));

    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size_of_vertices, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    self->length = size_of_vertices / sizeof(float);

    self->bind = ogl_bind;
    self->unbind = ogl_unbind;
    self->set_layout = ogl_set_layout;
}

void m_destroy_vertex_buffer_opengl(m_vertex_buffer* self){
    u32 id;
    memcpy(self->unimplemented_data, &id, sizeof(u32));
    glDeleteBuffers(1, &id);
    
    free(self->unimplemented_data);
}