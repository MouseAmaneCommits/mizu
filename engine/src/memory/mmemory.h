#pragma once

#include "../defines.h"
#include "stdlib.h"

MAPI void* m_allocate(size_t size);
MAPI void m_dealloc(void* handle);
MAPI b8 m_leak();