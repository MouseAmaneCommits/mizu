#pragma once

#include "../defines.h"

#define UNIMPLEMENTED_DATA_SIZE 20000

typedef struct {
    u32 x,y,width,height;
    const char* title;
    b8 closing;

    void* unimplemented_data;
}m_platform;


MAPI void m_init_platform(m_platform* platform, u32 x, u32 y, u32 width, u32 height, const char* title);

MAPI void m_update_platform(m_platform* platform);
MAPI b8 m_closing_platform(m_platform* platform);
MAPI void m_destroy_platform(m_platform* platform);