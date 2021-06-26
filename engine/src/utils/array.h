#pragma once

#include "../defines.h"

typedef struct{
    void** array;
    u32 index;
    u32 size;
    u32 size_of_type;
    
    u32 current_count;
}m_array;

MAPI void m_start_array(m_array* array, u32 size_of_type, u32 count);
MAPI void m_push_array(m_array* array, void* item);
MAPI void m_pop_array(m_array* array);