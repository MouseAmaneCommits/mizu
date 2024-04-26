#include "../../engine/src/core/application.h"
#include "../../engine/src/core/logger.h"
#include "../../engine/src/renderer/object/opengl/ogl_vertex_array.h"
#include "../../engine/src/renderer/object/opengl/ogl_vertex_buffer.h"
#include "../../engine/src/renderer/object/opengl/ogl_index_buffer.h"
#include "../../engine/src/renderer/object/opengl/ogl_shader.h"
#include "../../engine/src/renderer/object/opengl/ogl_texture.h"
#include "../../engine/src/renderer/renderer.h"
#include "../../engine/src/mesh/mesh.h"
#include <malloc.h>
#include <memory.h>

#include <windows.h>
#include <sys/time.h>
#include <glad/glad.h>
    const static f32 vertices_cube[] =
    {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };

    const static f32 texture_coords_cube[] =
    {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
    };

static m_camera* camera;
static m_mesh* mesh;

#include "../../engine/src/utils/array.h"

void print_array(m_array* array){
    for(u32 i = 0; i < array->index; i++){
        printf("%i\n", array->array[i]);
    }
}

void fl_start(){
    camera = QUICK_MALLOC(m_camera);
    camera->view = m_identity_matrix();
    camera->proj = m_perspective(1280/720, to_radians(10), from_radians(0.1f), from_radians(1000.0f));
    //camera->proj = m_orthographic(-1, 1, -1, 1, 0.001f, 1000.0f);
    camera->o_clear_color[0] = 0.0f; camera->o_clear_color[1] = 0.5f; camera->o_clear_color[2] = 1.0f; camera->o_clear_color[3] = 0.0f;
    m_bind_camera(camera);


    m_properties* properties = QUICK_MALLOC(m_properties);
    properties->pos = m_init_vec3(0, 0, 0);
    properties->sca = m_init_vec3(1, 1, 1);
    
    CREATE(m_texture, m_init_texture(texture, 0, "angel.jpg"), texture);
    properties->material = QUICK_MALLOC(m_material);
    properties->material->t_albedo = texture;
    mesh = m_load_from_file("sponza.obj", properties);

    m_scene* scene = m_create_scene();
    m_bind_scene(scene);
    scene->add_mesh(scene, mesh);
}

void fl_update(){
    if(m_pressing_key('S')){
        m_translate_camera(camera, m_init_vec3(0, 0, -0.1f));
    }
    if(m_pressing_key('W')){
        m_translate_camera(camera, m_init_vec3(0, 0, 0.1f));
    }
    if(m_pressing_key('D')){
        m_translate_camera(camera, m_init_vec3(-0.1f, 0, 0));
    }
    if(m_pressing_key('A')){
       m_translate_camera(camera, m_init_vec3(0.1f, 0, 0));
    }
    if(m_pressing_key('E')){
       m_translate_camera(camera, m_init_vec3(0, -0.1f, 0));
    }
    if(m_pressing_key('Q')){
       m_translate_camera(camera, m_init_vec3(0, 0.1f, 0));
    }
    if(m_pressing_key('C')){
        m_rotate_matrix(&camera->view, m_init_vec3(0, -0.1f, 0));
    }
    if(m_pressing_key('Z')){
        m_rotate_matrix(&camera->view, m_init_vec3(0, 0.1f, 0));
    }
    if(m_pressing_key('T')){
        m_rotate_matrix(&mesh->model, m_init_vec3(0, 0.1f, 0));
    }
}

void fl_stop(){
    
}

int main(int argc, char const *argv[])
{
    m_application game;
    m_init_application(&game);

    m_layer layer = {0};
    layer.attach = fl_start;
    layer.update = fl_update;
    layer.detach = fl_stop;

    m_push_application_layer(&game, &layer);

    m_run_application(&game, 1920/6, 1080/6, 1280, 720, "mizu");

    return 0;
}