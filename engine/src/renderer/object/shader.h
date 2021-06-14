#pragma once

#include "../../defines.h"

struct m_shader;

typedef struct {
    void* unimplemented_data;
    void(*bind)(struct m_shader*);
    void(*unbind)(struct m_shader*);
}m_shader;