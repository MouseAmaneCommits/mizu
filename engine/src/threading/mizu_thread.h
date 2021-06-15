#pragma once

#include "../defines.h"

#ifdef MIZU_PLATFORM_WINDOWS
#include "pthread_windows.h"
#else
#include <pthread.h>
#endif