#include "ogl_texture.h"

#include <memory.h>
#include <malloc.h>
#include "../../../core/logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

#define UNIMPLEMENTED_DATA_SIZE 6553

static void ogl_bind(m_texture* self){
    u32 id = 0;
    memcpy(&id, self->unimplemented_data, sizeof(u32));
    glBindTextureUnit(self->bind_slot, id);
}

static void ogl_unbind(m_texture* self){
    glBindTextureUnit(self->bind_slot, 0);
}

static void ogl_initialize(m_texture* self, const char* image){
    u32 id = 0;

    int width, height, channels;
    u8* data = stbi_load(image, &width, &height, &channels, 0);
    M_ASSERT(data);
    self->width = width;
    self->height = height;

    glCreateTextures(GL_TEXTURE_2D, 1, &id);
    glTextureStorage2D(id, 1, GL_RGB8, self->width, self->height);

    glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureSubImage2D(id, 0, 0, 0, self->width, self->height, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    memcpy(self->unimplemented_data, &id, sizeof(u32));
}

void m_init_texture_opengl(m_texture* self, u32 bind_slot, const char* image){
    self->unimplemented_data = malloc(UNIMPLEMENTED_DATA_SIZE);
    memset(self->unimplemented_data, 0, UNIMPLEMENTED_DATA_SIZE);
    ogl_initialize(self, image);

    self->bind_slot = bind_slot;

    self->bind = ogl_bind;
    self->unbind = ogl_unbind;
}