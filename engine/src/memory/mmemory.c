#include "mmemory.h"

#include "../core/logger.h"
#include <malloc.h>
#include <memory.h>

static u32 alloc_counter = 0;
static u32 dealloc_counter = 0;

void* m_allocate(size_t size){
    void* handle = NULL;
    handle = malloc(size);
    if(handle != NULL){
        ++alloc_counter;
    }
    else{
        M_ERROR("Cant allocate memory!");
    }
    return handle;
}

void m_dealloc(void* handle){
    if(handle != NULL){
        free(handle);
        ++dealloc_counter;
    }
}

b8 m_leak(){
    b8 ret = 0;
    if(alloc_counter != dealloc_counter){
        ret = TRUE;
    }else{
        ret = FALSE;
    }

    return ret;
}