#pragma once

#include "../../defines.h"

struct m_texture;

typedef enum{
    REPEAT,CLAMP_BORDER
}texture_mode;

typedef struct {
    void* unimplemented_data;
    
    u32 bind_slot;
    u32 width,height;
    void(*bind)(struct m_texture*);
    void(*unbind)(struct m_texture*);
}m_texture;

MAPI void m_init_texture(m_texture* texture, u32 bind_slot, const char* filename);
MAPI void m_destroy_texture(m_texture* texture);