#include "vector.h"

vec2 m_init_vec2(float x, float y){
    vec2 result;
    result.x = x;
    result.y = y;

    return result;
}

vec3 m_init_vec3(float x, float y, float z){
    vec3 result;
    result.x = x;
    result.y = y;
    result.z = z;

    return result;
}

vec4 m_init_vec4(float x, float y, float z, float w){
    vec4 result;
    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;

    return result;
}

// vec2
vec2 m_mul_vec2(vec2 left, vec2 right){
    vec2 result;
    result.x = left.x * right.x;
    result.y = left.y * right.y;

    return result;
}

vec2 m_add_vec2(vec2 left, vec2 right){
    vec2 result;
    result.x = left.x + right.x;
    result.y = left.y + right.y;

    return result;
}

vec2 m_div_vec2(vec2 left, vec2 right){
    vec2 result;
    result.x = left.x / right.x;
    result.y = left.y / right.y;

    return result;
}

vec2 m_sub_vec2(vec2 left, vec2 right){
    vec2 result;
    result.x = left.x - right.x;
    result.y = left.y - right.y;

    return result;
}

// vec3
vec3 m_mul_vec3(vec3 left, vec3 right){
    vec3 result;
    result.x = left.x * right.x;
    result.y = left.y * right.y;
    result.z = left.z * right.z;

    return result;
}

vec3 m_add_vec3(vec3 left, vec3 right){
    vec3 result;
    result.x = left.x + right.x;
    result.y = left.y + right.y;
    result.z = left.z + right.z;

    return result;
}

vec3 m_div_vec3(vec3 left, vec3 right){
    vec3 result;
    result.x = left.x / right.x;
    result.y = left.y / right.y;
    result.z = left.z / right.z;

    return result;
}

vec3 m_sub_vec3(vec3 left, vec3 right){
    vec3 result;
    result.x = left.x - right.x;
    result.y = left.y - right.y;
    result.z = left.z - right.z;

    return result;
}

// vec4
vec4 m_mul_vec4(vec4 left, vec4 right){
    vec4 result;
    result.x = left.x * right.x;
    result.y = left.y * right.y;
    result.z = left.z * right.z;
    result.w = left.w * right.w;

    return result;
}

vec4 m_add_vec4(vec4 left, vec4 right){
    vec4 result;
    result.x = left.x + right.x;
    result.y = left.y + right.y;
    result.z = left.z + right.z;
    result.w = left.w + right.w;

    return result;
}

vec4 m_div_vec4(vec4 left, vec4 right){
    vec4 result;
    result.x = left.x / right.x;
    result.y = left.y / right.y;
    result.z = left.z / right.z;
    result.w = left.w / right.w;

    return result;
}

vec4 m_sub_vec4(vec4 left, vec4 right){
    vec4 result;
    result.x = left.x - right.x;
    result.y = left.y - right.y;
    result.z = left.z - right.z;
    result.w = left.w - right.w;

    return result;
}