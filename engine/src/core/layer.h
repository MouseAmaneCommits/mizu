#pragma once

#include "../defines.h"

/*
@brief A layer in mizu is an abstracted part of an application that can be pushed to the mizu application layer stack.
The mizu application layer stack holds all of the application layers, starts, runs, and terminates all of the layers.
An application may have a "main" layer, which does all of the main stuff, and a "enemy-handler" layer, which handles all of the enemies, etc.
*/
typedef struct {
    void (*attach)(void); 
    void (*update)(void); 
    void (*detach)(void);
}m_layer;