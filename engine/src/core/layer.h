#pragma once

#include "../defines.h"

typedef struct {
    void (*attach)(void); 
    void (*update)(void); 
    void (*detach)(void);
}m_layer;