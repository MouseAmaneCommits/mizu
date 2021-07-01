#include "scene.h"

#include <malloc.h>
#include <memory.h>

static void add_mesh(m_scene* scene, m_mesh* mesh){
    m_push_array(scene->meshes, mesh);
}

static void remove_mesh(m_scene* scene, m_mesh* mesh){
    // TODO: to be added
}

m_scene* m_create_scene(){
    m_scene* scene = QUICK_MALLOC(m_scene);
    memset(scene, 0, sizeof(m_scene));

    scene->meshes = QUICK_MALLOC(m_array);
    m_start_array(scene->meshes, sizeof(m_mesh*), 1);
    scene->add_mesh = add_mesh;
    scene->remove_mesh = remove_mesh;

    
    return scene;
}