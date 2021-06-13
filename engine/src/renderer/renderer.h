#pragma once

#include "context/context.h"
#include "../defines.h"
#include "../platform/platform.h"

MAPI void m_init_renderer(m_platform* platform, m_renderer_api api);
MAPI void m_begin_frame();
//MAPI void m_submit(m_vao* vao, m_shader* shader); // connects to the context, to render the vao and shader
MAPI void m_end_frame();

MAPI void m_reshape_renderer(u32 width, u32 height);
MAPI b8 m_initialized_renderer();