#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <unistd.h>

#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display *, GLXFBConfig, GLXContext, Bool, const int *);

namespace tfefs {
    

    Display *display = XOpenDisplay(nullptr);

    static bool ctxErrorOccured = false;
    static int ctxErrorHandler(Display *dpy, XErrorEvent *ev)
    {
        ctxErrorOccured = true;
        return 0;
    }

    static int visual_attribs[] =
        {
            GLX_X_RENDERABLE, True,
            GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
            GLX_RENDER_TYPE, GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
            GLX_RED_SIZE, 8,
            GLX_GREEN_SIZE, 8,
            GLX_BLUE_SIZE, 8,
            GLX_ALPHA_SIZE, 8,
            GLX_DEPTH_SIZE, 24,
            GLX_STENCIL_SIZE, 8,
            GLX_DOUBLEBUFFER, True,
            None};

    int glx_major, glx_minor;

    int fbcount;

    GLXFBConfig *fbc = glXChooseFBConfig(display,
                                         DefaultScreen(display),
                                         visual_attribs,
                                         &fbcount);

    int best_fbc = -1,
        worst_fbc = -1,
        best_num_samp = -1,
        worst_num_samp = 999;

    

    GLXFBConfig bestFbc = fbc[best_fbc];
    XVisualInfo *vi = glXGetVisualFromFBConfig(display, bestFbc);
    XSetWindowAttributes swa;
    Colormap cmap;
    
    Window win = XCreateWindow(display, RootWindow(display, vi->screen),
                               0, 0, 100, 100, 0, vi->depth, InputOutput,
                               vi->visual,
                               CWBorderPixel | CWColormap | CWEventMask, &swa);

    const char *glxExts = glXQueryExtensionsString(display,
                                                   DefaultScreen(display));

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    GLXContext ctx = 0;
    //ctxErrorOccured = false;
}