#include "ogl_shader.h"

#include <memory.h>
#include "../../../core/logger.h"

#define UNIMPLEMENTED_DATA_SIZE 6553

#include <stddef.h>
#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

const char * GetGLErrorStr(GLenum err)
{
    switch (err)
    {
    case GL_NO_ERROR:          return "No error";
    case GL_INVALID_ENUM:      return "Invalid enum";
    case GL_INVALID_VALUE:     return "Invalid value";
    case GL_INVALID_OPERATION: return "Invalid operation";
    case GL_STACK_OVERFLOW:    return "Stack overflow";
    case GL_STACK_UNDERFLOW:   return "Stack underflow";
    case GL_OUT_OF_MEMORY:     return "Out of memory";
    default:                   return "Unknown error";
    }
}


#define GL_CHECK(X) X; do{\
    const GLenum err = glGetError(); if(GL_NO_ERROR == err)break; M_ERROR("Opengl error! %s", GetGLErrorStr(err));\
}while(TRUE)

static void ogl_bind(m_shader* self){
    u32 shader_id = 0;
    memcpy(&shader_id, self->unimplemented_data, sizeof(u32));
    printf("%i\n", shader_id);
    glUseProgram(shader_id);
}

static void ogl_unbind(m_shader* self){
    glUseProgram(0);
}

static u32 compile_shader(u32 type, const char* src){
    u32 id = glCreateShader(type);
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    return id;

    // GLboolean compiled = GL_FALSE;
    // glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    // if(compiled != GL_TRUE){
        
    //     char info_log[1024];
    //     u32 length = 0;
    //     glGetShaderInfoLog(id, 1024, &length, info_log);

    //     M_ERROR("Failed to compile shader! GL error: %s", info_log);
    // }

}

static void ogl_create_shader(m_shader* self, const char* vs, const char* fs){
    u32 vertex_shader = compile_shader(GL_VERTEX_SHADER, vs);
    u32 fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fs);

    u32 program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    memcpy(self->unimplemented_data, &program, sizeof(u32));
    // GLint linked;
    // glGetProgramiv(program, GL_LINK_STATUS, &linked);

    // if(linked != GL_TRUE){
    //     char* info_log = (char*)malloc(sizeof(char) * 1024);
    //     int length = 0;
    //     glGetProgramInfoLog(program, 1024, &length, info_log);
    //     M_ERROR("Failed to link shaderProgram! %s", info_log);
    // }
    
}

static char* read_file(const char* file_name){
    FILE* file = fopen(file_name, "rt");
    if(file == NULL){
        M_ERROR("cannot open %s for shader creation!", file_name);
    }

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    rewind(file);

    char* buffer = malloc(sizeof(char) * (file_size + 1));
    memset(buffer, 0, sizeof(char) * (file_size + 1));
 
    fread(buffer, sizeof(char), file_size, file);

    buffer[file_size] = '\0';

    fclose(file);

    return buffer;
}

void m_init_shader_opengl(m_shader* self, const char* vFilename, const char* fFilename){
    self->unimplemented_data = malloc(UNIMPLEMENTED_DATA_SIZE);
    ogl_create_shader(self, read_file(vFilename), read_file(fFilename));
    
    self->bind = ogl_bind;
    self->unbind = ogl_unbind;
}