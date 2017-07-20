/*
MIT License

Copyright (c) 2017 Curi0 <curi0minecraft@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Compile with : gcc -Wall -fPIC -shared -o blackframe.so main.c -lGL -ldl
Run using : LD_PRELOAD=blackframe.so **GAMEEXECUTABLE**

VSync recommended when running a game to keep the frame rate consistent.

WARNING : This program causes flickers on screen which are (fps / 2) and may be annoying.

 */ 
 
#define _GNU_SOURCE
#include <dlfcn.h>
#include <GL/glx.h>

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
        real_dlsym= _dl_sym(RTLD_NEXT, "dlsym", dlsym);

    if (!strcmp(name,"dlsym")) 
        return (void*)dlsym; // Override dlsym with our dlsym
    if (!strcmp(name,"glXSwapBuffers")) 
        return (void*)glXSwapBuffers; // Override glXSwapBuffers
    
    return real_dlsym(handle,name);
}

