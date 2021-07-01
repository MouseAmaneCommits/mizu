#pragma once

#include "../defines.h"
#include "../mesh/mesh.h"
#include "../utils/array.h"

typedef struct m_scene {
    m_array* meshes;
    void(*add_mesh)(struct m_scene*, m_mesh*);
    void(*remove_mesh)(struct m_scene*, m_mesh*);
}m_scene;

MAPI m_scene* m_create_scene();