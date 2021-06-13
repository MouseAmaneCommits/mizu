#pragma once

#include "../defines.h"
#include "platform.h"

MAPI b8 m_closing_win32(m_platform* platform);
MAPI b8 m_closing_linux(m_platform* platform);

MAPI void m_update_for_win32(m_platform* platform);
MAPI void m_destroy_for_win32(m_platform* platform);

MAPI void m_update_for_linux(m_platform* platform);
MAPI void m_destroy_for_linux(m_platform* platform);

MAPI void m_init_platform_for_win32(m_platform* platform);
MAPI void m_init_platform_for_linux(m_platform* platform);