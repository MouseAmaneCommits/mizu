#include "editor.h"
#include "../../engine/src/core/application.h"

int main(){ 
    m_application app;
    m_layer editor_layer;
    editor_layer.attach = &editor_layer_start;
    editor_layer.update = &editor_layer_update;
    editor_layer.detach = &editor_layer_destroy;
    
    m_init_application(&app);
    m_push_application_layer(&app, &editor_layer);

    m_run_application(&app, 0, 0, 1280, 720, "mizu editor");

    return 0;
}