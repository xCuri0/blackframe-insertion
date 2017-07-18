#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glx.h>
#include <unistd.h>
int black = 0;

void (*_glXSwapBuffers)(Display* dpy, GLXDrawable drawable);
void *_dl_sym(void *, const char *, void *);

void blackframe(){
    if (black == 1){
        // Set frame to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
        glClear(GL_COLOR_BUFFER_BIT);
        black = 0; // Next frame will not be hacked
    }else
        black = 1; // Next frame will be black
}
void glXSwapBuffers(Display* dpy, GLXDrawable drawable)
{
    if (_glXSwapBuffers == NULL)
        _glXSwapBuffers = _dl_sym(RTLD_NEXT, "glXSwapBuffers",glXSwapBuffers);
    
    blackframe();
    _glXSwapBuffers(dpy,drawable);
}

// hacking dlsym is required for some OpenGL applications (GLFW ?)
void *dlsym(void *handle, const char *name)
{
    static void * (*real_dlsym)(void *, const char *)=NULL;
    if (real_dlsym == NULL)
        real_dlsym=_dl_sym(RTLD_NEXT, "dlsym", dlsym);

    if (!strcmp(name,"dlsym")) 
        return (void*)dlsym;
    if (!strcmp(name,"glXSwapBuffers")) 
        return (void*)glXSwapBuffers;
    
    return real_dlsym(handle,name);
}

