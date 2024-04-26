#pragma once

#include "../defines.h"
#include "layer.h"
#include "../platform/platform.h"
#include "../scene/scene_manager.h"

#define MAX_LAYER_COUNT 16

/*
@brief The application to be ran with mizu.
*/
typedef struct {
    m_layer* layers[MAX_LAYER_COUNT];
    u32 layer_index;

    u32 x, y, width, height;
    const char* title;
    m_platform platform;
}m_application;

/*
@brief Initializes the mizu engine and initializes memory with the application
@param app A pointer to an instance of m_application. Expects app to be valid memory.
*/
MAPI void m_init_application(m_application* app);

/*
@brief Adds a layer to the application
@param app
@param layer A pointer to the layer of which to add to the application.
*/
MAPI void m_push_application_layer(m_application* app, m_layer* layer);

/*
@brief Runs the application loop, thus stalling the main thread.
@param app
@param x The x location of the window
@param y The y location of the window
@param width The width of the window
@param height The height of the window
@param title The title of the window and application
*/
MAPI void m_run_application(m_application* app, u32 x, u32 y, u32 width, u32 height, const char* title);