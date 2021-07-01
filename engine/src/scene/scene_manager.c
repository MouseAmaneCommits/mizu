#include "scene_manager.h"

#include "../core/logger.h"
#include <stdio.h>

static m_scene* gScene = NULL;

void m_bind_scene(m_scene* scene){
    gScene = scene;
}

void m_update_scene_manager(){
    if(gScene == NULL){ // if no mesh is bound, no need to update
        return;
    }

    for(u32 i = 0; i < gScene->meshes->current_count; i++){
        (((m_mesh**)gScene->meshes->array)[i])->draw(((m_mesh**)gScene->meshes->array)[i]);
    }
}