#include <stdio.h>
#include "../../engine/src/core/application.h"
#include "../../engine/src/core/logger.h"

#include <glad/glad.h>

void fl_start(){
}

void fl_update(){
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
