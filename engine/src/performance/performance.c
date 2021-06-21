#include "performance.h"

#include <sys/time.h>

static clock_t begin;
static clock_t end;


void time_it_begin(){
    begin = clock();
}

void time_it_end(){
    end = clock();
}

f32 time_get_elapsed(){
    return (float) (end-begin);
}