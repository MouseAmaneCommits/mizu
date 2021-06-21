#pragma once

#include "../../defines.h"
#include "../../platform/platform.h"

typedef enum {
    OPENGL,
}m_renderer_api;

typedef struct {
    m_platform* platform;
    void (*init)(void);
    void (*begin_frame)(void);
    void (*end_frame)(void);
    void(*reshape)(u32, u32);
    void(*set_clear_color)(float, float, float, float);
    m_renderer_api api;
}m_context;

MAPI void m_init_context(m_context* context, m_platform* platform, m_renderer_api api);