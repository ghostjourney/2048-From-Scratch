#pragma once
#include "ctx.hpp"

namespace tfefs {
    inline static bool isExtensionSupported(const char *extlist, const char *extension)
    {
        const char *start;
        const char *where, *terminator;

        where = strchr(extension, ' ');
        if (where || *extension == '\0')
            return false;

        for (start = extlist;;)
        {
            where = strstr(start, extension);
            if (!where)
                break;
            terminator = where + strlen(extension);

            if (where == start || *(where - 1) == ' ')
                if (*terminator == ' ' || *terminator == '\0')
                    return true;

            start = terminator;
        }
        return false;
    }

    inline static bool isXDisplay() {
        if (!display)
        {
            std::cout << "Failed to open X display.\n";
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    inline static bool isglXQueryVersion () {
        if (!glXQueryVersion(display, &glx_major, &glx_minor) ||
            ((glx_major == 1) && (glx_minor < 3)) || (glx_major < 1))
        {

            std::cout << "Invalid GLX version.\n";
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    inline static bool isFBC() {
        if (!fbc)
        {
            std::cout << "Failed to retrieve a framebuffer config.\n";
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    inline void getVisualConfig() {
        int i;
        for (i = 0; i < fbcount; ++i)
        {
            XVisualInfo *vi = glXGetVisualFromFBConfig(display, fbc[i]);
            if (vi)
            {
                int samp_buf, samples;
                glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
                glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLES, &samples);

                std::cout << "  Matching fbconfig "
                        << i
                        << ", visual ID 0x"
                        << vi->visualid
                        << "2x: SAMPLE_BUFFERS = "
                        << samp_buf
                        << ", SAMPLES = "
                        << samples << "\n";

                if (best_fbc < 0 || samp_buf && samples > best_num_samp)
                    best_fbc = i, best_num_samp = samples;
                if (worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
                    worst_fbc = i, worst_num_samp = samples;
            }
            XFree(vi);
        }

        return;
    }

    inline void setColorMap() {
        swa.colormap = cmap = XCreateColormap(display,
                                            RootWindow(display, vi->screen),
                                            vi->visual, AllocNone);
        swa.background_pixmap = None;
        swa.border_pixel = 0;
        swa.event_mask = StructureNotifyMask;

        return;
    }

    inline bool isWindow() {
        if (!win)
        {
            std::cout << "Failed to create window\n";
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    inline void mapWindow() {
        XFree(vi);
        XStoreName(display, win, "2048");
        std::cout << "Mapping window\n";
        XMapWindow(display, win);

        return;
    }

    inline void setAttribsFn() {
        glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
        glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");
        
        return;
    }

    // check for openGL context validity
    inline bool isGL() {
        if (ctxErrorOccured || !ctx)
        {
            std::cout << "Failed to create an OpenGL context\n";
            return EXIT_FAILURE;
        }
    }

    inline void setOldHandler() {
        int (*oldHandler)(Display *, XErrorEvent *) =
        XSetErrorHandler(&ctxErrorHandler);

        if (!isExtensionSupported(glxExts, "GLX_ARB_create_context") ||
        !glXCreateContextAttribsARB)
        {
            std::cout << "glXCreateContextAttribsARB() not found\n  ... using old-style GLX context\n";
            ctx = glXCreateNewContext(display, bestFbc, GLX_RGBA_TYPE, 0, True);

        } else {

        int context_attribs[] =
            {
                GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
                GLX_CONTEXT_MINOR_VERSION_ARB, 0,
                None};

            std::cout << "Creating Context\n";
            ctx = glXCreateContextAttribsARB(display, bestFbc, 0,
                                            True, context_attribs);

            XSync(display, False);
            if (!ctxErrorOccured && ctx)
            {
                std::cout << "Created GL 3.0 context\n";
            }
            else
            {
                context_attribs[1] = 1;
                context_attribs[3] = 0;

                ctxErrorOccured = false;

                std::cout << "Failed to create GL 3.0 context\n ... using old-style GLX context\n";
                ctx = glXCreateContextAttribsARB(display, bestFbc, 0, True, context_attribs);
            }
        }
        XSync(display, False);
        XSetErrorHandler(oldHandler);

        

        if (!glXIsDirect(display, ctx))
        {
            std::cout << "Indirect GLX rendering context obtained\n";
        } else {
            std::cout << "Direct GLX rendering context obtained\n";
        }
    }

    inline void gl_setup () {
        glXMakeCurrent( display, win, ctx );

        glClearColor( 0, 0.5, 1, 1);
        glClear( GL_COLOR_BUFFER_BIT );
        glXSwapBuffers( display, win);
        sleep( 1 );

        glClearColor ( 1, 0.5, 0, 1 );
        glClear ( GL_COLOR_BUFFER_BIT );
        glXSwapBuffers ( display, win );

        sleep( 10 );

        glXMakeCurrent( display, 0, 0 );
        glXDestroyContext( display, ctx );

        XDestroyWindow( display, win );
        XFreeColormap( display, cmap );
        XCloseDisplay( display );
        }
        
}