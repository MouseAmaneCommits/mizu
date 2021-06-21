#include "opengl_context.h"

#include <memory.h>
#include "../../../core/logger.h"

#ifdef MIZU_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#include <glad/glad.h>

static m_context* self;


/*- Global Variables*/
#ifdef MIZU_PLATFORM_WINDOWS // Windows global variables
static HWND hwnd;
static HDC ourWindowHandleToDeviceContext;
#endif

void ogl_init(){
    #ifdef MIZU_PLATFORM_WINDOWS
    memcpy(&hwnd, self->platform->unimplemented_data, sizeof(HWND));

    		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		ourWindowHandleToDeviceContext = GetDC(hwnd);

		int  letWindowsChooseThisPixelFormat;
		letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd); 
		SetPixelFormat(ourWindowHandleToDeviceContext,letWindowsChooseThisPixelFormat, &pfd);

		HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
		wglMakeCurrent (ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);
        M_INFO("Created opengl context!");
    #endif

	if(!gladLoadGL()){
		M_FATAL("Failed to load glad!");
	}
}

void ogl_begin(){
	glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ogl_end(){
	glDisable(GL_DEPTH_TEST);

    #ifdef MIZU_PLATFORM_WINDOWS
    SwapBuffers(ourWindowHandleToDeviceContext);
    #endif
}

void ogl_reshape(u32 width, u32 height){
	glViewport(0, 0, width, height);
}

void ogl_clear_color(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
}

void m_init_context_ogl(m_context* context){
    context->init = ogl_init;
    context->begin_frame = ogl_begin;
    context->end_frame = ogl_end;
	context->reshape = ogl_reshape;
	context->set_clear_color = ogl_clear_color;
    self = context;
}