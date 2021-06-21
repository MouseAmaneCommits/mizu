#include "script.h"

void m_init_script(m_script* self, void(*start)(void), void(*update)(void)){
    self->start = start;
    self->update = update;
}