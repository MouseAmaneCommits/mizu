#include "ogl_texture.h"

#include <memory.h>
#include <malloc.h>
#include "../../../core/logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

#define UNIMPLEMENTED_DATA_SIZE 6553

typedef struct {
    u32 id;
}internal_memory;

static void ogl_bind(m_texture* self){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTextureUnit(self->bind_slot, ((internal_memory*)self->unimplemented_data)->id);
}

static void ogl_unbind(m_texture* self){
    glDisable(GL_BLEND);
    glBindTextureUnit(self->bind_slot, 0);
}

static void ogl_initialize(m_texture* self, const char* image){
    u32 id = 0;

    int width, height, channels;
    stbi_set_flip_vertically_on_load(TRUE);  
    u8* data = stbi_load(image, &width, &height, &channels, 0);
    M_ASSERT(data);
    self->width = width;
    self->height = height;

    glCreateTextures(GL_TEXTURE_2D, 1, &id);
    glTextureStorage2D(id, 1, GL_RGB8, self->width, self->height);

    glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTextureSubImage2D(id, 0, 0, 0, self->width, self->height, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    ((internal_memory*)self->unimplemented_data)->id = id;
}

void m_init_texture_opengl(m_texture* self, u32 bind_slot, const char* image){
    self->unimplemented_data = QUICK_MALLOC(internal_memory);
    ogl_initialize(self, image);

    self->bind_slot = bind_slot;

    self->bind = ogl_bind;
    self->unbind = ogl_unbind;
}