#pragma once

#define QUICK_MALLOC(X) (X*)malloc(sizeof(X))
#define CREATE(type, func, name) type* name = QUICK_MALLOC(type); func;

/*- Typedefs -*/
typedef void (*fn_ptr);

// unsigned
typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

// signed
typedef signed long long s64;
typedef signed int s32;
typedef signed short s16;
typedef signed char s8;

// floating points
typedef double f64;
typedef float f32;

// booleans
typedef int b32;
typedef char b8;


/*- Defines -*/
#if defined(MIZU_BUILD_SHARED)
#define MAPI __declspec(dllexport)
#elif defined(MIZU_BUILD_STATIC)
#define MAPI extern
#else
#define MAPI __declspec(dllimport)
#endif

#if defined(_WIN32) || defined(WIN32)

    #if !defined(_WIN64) && !defined(WIN64)
        #error mizu does not support x64 architecture
    #endif

#define MIZU_PLATFORM_WINDOWS

#elif defined(__linux__)
#define MIZU_PLATFORM_LINUX
#elif defined(__unix__)
#define MIZU_PLATFORM_LINUX
#elif defined(__APPLE__)
#define MIZU_PLATFORM_MAC
#endif

#define TRUE 1
#define FALSE 0