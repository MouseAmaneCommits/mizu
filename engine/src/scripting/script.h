#pragma once

#include "../defines.h"

typedef struct {
    void(*start)(void);
    void(*update)(void);
}m_script;

MAPI void m_init_script(m_script* script, void(*start)(void), void(*update)(void));