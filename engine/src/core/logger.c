#include "logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include <string.h>

void m_log(m_log_level level, const char* msg, ...){
    const char* levels[] = {
        "[Fatal]: ",
        "[Error]: ",
        "[Warning]: ",
        "[Info]: ",
        "[Trace]: ",
        "[Debug]: "
    };

    va_list args;

    va_start(args, msg);

    char full_msg[2048];
    memset(full_msg, 0, sizeof(full_msg));
    strcat(full_msg, levels[level]);
    strcat(full_msg, msg);
    strcat(full_msg, "\n");
    vprintf(full_msg, args);

    va_end(args);
}