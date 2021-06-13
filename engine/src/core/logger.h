#pragma once

#include "../defines.h"

typedef enum {
    LOG_LEVEL_FATAL=0,
    LOG_LEVEL_ERROR=1,
    LOG_LEVEL_WARN=2,
    LOG_LEVEL_INFO=3,
    LOG_LEVEL_TRACE=4,
    LOG_LEVEL_DEBUG=5
}m_log_level;

MAPI void m_log(m_log_level level, const char* msg, ...);

#define M_FATAL(X, ...) m_log(LOG_LEVEL_FATAL, X, ##__VA_ARGS__)
#define M_ERROR(X, ...) m_log(LOG_LEVEL_ERROR, X, ##__VA_ARGS__)
#define M_WARN(X, ...) m_log(LOG_LEVEL_WARN, X, ##__VA_ARGS__)
#define M_INFO(X, ...) m_log(LOG_LEVEL_INFO, X, ##__VA_ARGS__)
#define M_TRACE(X, ...) m_log(LOG_LEVEL_TRACE, X, ##__VA_ARGS__)
#define M_DEBUG(X, ...) m_log(LOG_LEVEL_DEBUG, X, ##__VA_ARGS__)

#define M_ASSERT(expr)\
if(expr){\
    \
}else{\
    m_log(LOG_LEVEL_FATAL, "%s failed! On line %i, in file %s.", #expr, __LINE__, __FILE__);\
}
