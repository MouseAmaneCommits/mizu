#pragma once

#include "../../defines.h"

struct m_uniform_buffer;

typedef struct {
    void* unimplemented_data;
    const char* name;

    void(*bind)(struct m_uniform_buffer*);
    void(*unbind)(struct m_uniform_buffer*);
}m_uniform_buffer;

// Give the amount of memory to allocate to the uniform buffer
MAPI void m_init_uniform_buffer(m_uniform_buffer* buffer, const char* name, u32 buffer_size);