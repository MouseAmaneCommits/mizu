#include "platform.h"

#include <memory.h>
#include <malloc.h>

#include "../memory/mmemory.h"

#include "platform_backend.h"

void m_init_platform(m_platform* self, u32 x, u32 y, u32 width, u32 height, const char* title){
    self->x = x;
    self->y = y;
    self->width = width;
    self->height = height;
    self->title = title;
    
    self->unimplemented_data = malloc(sizeof(u8) * UNIMPLEMENTED_DATA_SIZE);
    memset(self->unimplemented_data, 0, sizeof(u8) * UNIMPLEMENTED_DATA_SIZE);

    #ifdef MIZU_PLATFORM_WINDOWS
    m_init_platform_for_win32(self);
    #elif MIZU_PLATFORM_LINUX
    m_init_platform_for_linux(self);
    #endif
}

void m_update_platform(m_platform* self){
    #ifdef MIZU_PLATFORM_WINDOWS
    m_update_for_win32(self);
    #elif MIZU_PLATFORM_LINUX
    m_update_for_linux(self);
    #endif
}

b8 m_closing_platform(m_platform* self){
    #ifdef MIZU_PLATFORM_WINDOWS
    return m_closing_win32(self);
    #elif MIZU_PLATFORM_LINUX
    return m_closing_linux(self);
    #endif
}

void m_destroy_platform(m_platform* self){
    #ifdef MIZU_PLATFORM_WINDOWS
    m_destroy_for_win32(self);
    #elif MIZU_PLATFORM_LINUX
    m_destroy_for_linux(self);  
    #endif

    free(self->unimplemented_data);
}