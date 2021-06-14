#pragma once

#include "../defines.h"

typedef struct {
    float x,y;
}vec2;

typedef struct {
    float x,y,z;
}vec3;

typedef struct {
    float x,y,z,w;
}vec4;

/*- Initialization functions -*/
MAPI vec2 m_init_vec2(float x, float y);
MAPI vec3 m_init_vec3(float x, float y, float z);
MAPI vec4 m_init_vec4(float x, float y, float z, float w);

/*- Math -*/

// vec2
MAPI vec2 m_mul_vec2(vec2 left, vec2 right);
MAPI vec2 m_add_vec2(vec2 left, vec2 right);
MAPI vec2 m_div_vec2(vec2 left, vec2 right);
MAPI vec2 m_sub_vec2(vec2 left, vec2 right);

// vec3
MAPI vec3 m_mul_vec3(vec3 left, vec3 right);
MAPI vec3 m_add_vec3(vec3 left, vec3 right);
MAPI vec3 m_div_vec3(vec3 left, vec3 right);
MAPI vec3 m_sub_vec3(vec3 left, vec3 right);

// vec4
MAPI vec4 m_mul_vec4(vec4 left, vec4 right);
MAPI vec4 m_add_vec4(vec4 left, vec4 right);
MAPI vec4 m_div_vec4(vec4 left, vec4 right);
MAPI vec4 m_sub_vec4(vec4 left, vec4 right);