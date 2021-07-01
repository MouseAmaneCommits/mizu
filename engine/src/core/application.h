#pragma once

#include "../defines.h"
#include "layer.h"
#include "../platform/platform.h"
#include "../scene/scene_manager.h"

#define MAX_LAYER_COUNT 16

typedef struct {
    m_layer* layers[MAX_LAYER_COUNT];
    u32 layer_index;

    u32 x, y, width, height;
    const char* title;
    m_platform platform;
}m_application;

MAPI void m_init_application(m_application* app);
MAPI void m_push_application_layer(m_application* app, m_layer* layer);
MAPI void m_run_application(m_application* app, u32 x, u32 y, u32 width, u32 height, const char* title);