#pragma once

#include "../defines.h"
#include "vector.h"

typedef struct {
    float matrix[4][4];
}mat4;

MAPI mat4 m_fill_matrix(float m[4][4]);
MAPI mat4 m_identity_matrix();
MAPI mat4 m_init_matrix(float diagonal);
MAPI mat4 m_zero();

MAPI mat4 m_add_matrix(mat4 left, mat4 right);
MAPI mat4 m_sub_matrix(mat4 left, mat4 right);

MAPI void m_translate_matrix(mat4* left, vec3 value);
MAPI void m_rotate_matrix(mat4* left, vec3 value);

MAPI mat4 m_mul_matrix(mat4 left, mat4 right);

MAPI float* m_convert_matrix_to_float_array(mat4 mat);