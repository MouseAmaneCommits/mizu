#include "mat4.h"

#include <malloc.h>
#include <memory.h>

mat4 m_identity_matrix(){
    mat4 m;

    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            m.matrix[y][x] = 0;
        }
    }

    m.matrix[0][0] = 1;
    m.matrix[1][1] = 1;
    m.matrix[2][2] = 1;
    m.matrix[3][3] = 1;
    
    return m;
}

mat4 m_init_matrix(float diagonal){
    mat4 m;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            m.matrix[y][x] = 0;
        }
    }

    m.matrix[0][0] = diagonal;
    m.matrix[1][1] = diagonal;
    m.matrix[2][2] = diagonal;
    m.matrix[3][3] = diagonal;

    return m;
}

mat4 m_zero(){
    mat4 m;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            m.matrix[y][x] = 0;
        }
    }

    return m;
}

mat4 m_add_matrix(mat4 left, mat4 right){
    mat4 result;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            result.matrix[i][j] = left.matrix[i][j] + right.matrix[i][j];
        }
    }

    return result;
}

mat4 m_sub_matrix(mat4 left, mat4 right){
    mat4 result;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            result.matrix[i][j] = left.matrix[i][j] - right.matrix[i][j];
        }
    }

    return result;
}

mat4 m_mul_matrix(mat4 left, mat4 right){
    mat4 result;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            float num = 0;
            for(int k = 0; k < 4; k++){
                num += left.matrix[i][k] * right.matrix[k][j];
            }
            result.matrix[i][j] = num;
        }
    }

    return result;
}

void m_translate_matrix(mat4* left, vec3 value){
    left->matrix[3][0] += value.x;
    left->matrix[3][1] += value.y;
    left->matrix[3][2] += value.z;

    return left;
}

float* m_convert_matrix_to_float_array(mat4 mat){
    float* array = malloc(sizeof(float) * 16);
    memset(array, 0, sizeof(float) * 16);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            int position = i * 4 + j;
            array[position] = mat.matrix[i][j];
        }
    }

    return array;
}