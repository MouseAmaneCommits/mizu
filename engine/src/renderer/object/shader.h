#pragma once

#include "../../defines.h"

#include "../../math/math.h"

struct m_shader;

typedef struct {
    void* unimplemented_data;
    void(*bind)(struct m_shader*);
    void(*unbind)(struct m_shader*);
    
    // uniforms
    void(*set_int)(struct m_shader*, const char*, int);
    void(*set_float)(struct m_shader*, const char*, float);
    void(*set_vec2)(struct m_shader*, const char*, vec2);
    void(*set_vec3)(struct m_shader*, const char*, vec3);
    void(*set_vec4)(struct m_shader*, const char*, vec4);
    void(*set_mat4)(struct m_shader*, const char*, mat4);
}m_shader;