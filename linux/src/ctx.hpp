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

namespace tfefs {
    #define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
    #define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
    typedef GLXContext (*glXCreateContextAttribsARBProc)(Display *, GLXFBConfig, GLXContext, Bool, const int *);

    Display *display = XOpenDisplay(nullptr);

    static bool ctxErrorOccured = false;
    static int ctxErrorHandler(Display *dpy, XErrorEvent *ev)
    {
        ctxErrorOccured = true;
        return 0;
    }

    
}