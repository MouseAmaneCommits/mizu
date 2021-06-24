#pragma once

#include "../uniform_buffer.h"
#include "../shader.h"

// Give the amount of memory to allocate to the uniform buffer
MAPI void m_init_uniform_buffer_opengl(m_uniform_buffer* buffer, const char* name, u32 buffer_size);