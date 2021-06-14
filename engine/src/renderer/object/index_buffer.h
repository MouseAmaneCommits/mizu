#pragma once

#include "../../defines.h"

struct m_index_buffer;

typedef struct {
    void* unimplemented_data;
    u32 count;

    void(*bind)(struct m_index_buffer*);
    void(*unbind)(struct m_index_buffer*);
}m_index_buffer;