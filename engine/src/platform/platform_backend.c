#include "platform_backend.h"

#include "../renderer/renderer.h"

#include "../core/logger.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef MIZU_PLATFORM_WINDOWS
#include <windows.h>

LRESULT window_proc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam){
    switch(Msg){
        case WM_CLOSE:
            PostQuitMessage(0);
            return;
        case WM_SIZE:
            if(m_initialized_renderer())
                m_reshape_renderer(LOWORD(lParam), HIWORD(lParam));
    }
    
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}
#endif


void m_init_platform_for_win32(m_platform* self){
    #ifdef MIZU_PLATFORM_WINDOWS
    // get instance to use for window creation
    HINSTANCE instance = GetModuleHandle(NULL);

    WNDCLASS wc = {0};
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)(NULL);
    wc.hCursor = NULL;
    wc.hIcon = NULL;
    wc.hInstance = instance;
    wc.lpfnWndProc = window_proc;
    wc.lpszClassName = "class";
    wc.lpszMenuName = NULL;
    wc.style = NULL;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(NULL, "class", self->title, WS_SIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_MINIMIZEBOX, self->x, self->y, self->width, self->height, NULL, NULL, instance, NULL);
    ShowWindow(hwnd, SW_SHOW);

    memcpy(self->unimplemented_data, &hwnd, sizeof(hwnd));

    #endif
}

void m_init_platform_for_linux(m_platform* self){

}


void m_update_for_win32(m_platform* self){
    #ifdef MIZU_PLATFORM_WINDOWS
    HWND hwnd = NULL;
    memcpy(&hwnd, self->unimplemented_data, sizeof(HWND));
    
    MSG msg;
    
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    if (msg.message == WM_QUIT){
        self->closing = TRUE;
    }

#endif
}

void m_destroy_for_win32(m_platform* self){
    #ifdef MIZU_PLATFORM_WINDOWS
    HWND hwnd = NULL;
    memcpy(&hwnd, self->unimplemented_data, sizeof(HWND));
    ShowWindow(hwnd, SW_HIDE);
    DestroyWindow(hwnd);
    #endif
}

void m_update_for_linux(m_platform* self){

}

void m_destroy_for_linux(m_platform* self){

}


b8 m_closing_win32(m_platform* self){
    #ifdef MIZU_PLATFORM_WINDOWS
    return self->closing;
    #endif
}

b8 m_closing_linux(m_platform* self){
    
}