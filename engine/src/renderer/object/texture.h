#pragma once

#include "../../defines.h"

struct m_texture;

typedef struct {
    void* unimplemented_data;
    
    u32 bind_slot;
    u32 width,height;
    void(*bind)(struct m_texture*);
    void(*unbind)(struct m_texture*);
}m_texture;