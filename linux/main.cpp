#include "src/ctx.hpp"
#include "src/util.hpp"


int main(int argc, char *argv[])
{

    
    // sleep(3);

    if (!display)
    {
        std::cout << "Failed to open X display.\n";
        return EXIT_FAILURE;
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

    if (!glXQueryVersion(display, &glx_major, &glx_minor) ||
        ((glx_major == 1) && (glx_minor < 3)) || (glx_major < 1))
    {

        std::cout << "Invalid GLX version.\n";
        return EXIT_FAILURE;
    }

    std::cout << "Getting matching framebuffer config.\n";
    int fbcount;

    GLXFBConfig *fbc = glXChooseFBConfig(display,
                                         DefaultScreen(display),
                                         visual_attribs,
                                         &fbcount);

    if (!fbc)
    {
        std::cout << "Failed to retrieve a framebuffer config.\n";
        return EXIT_FAILURE;
    }

    std::cout << "Found " << fbcount << " matching FB configs.\n";
    std::cout << "Getting XVisualInfos\n";

    int best_fbc = -1,
        worst_fbc = -1,
        best_num_samp = -1,
        worst_num_samp = 999;

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

    GLXFBConfig bestFbc = fbc[best_fbc];
    XFree(fbc);
    XVisualInfo *vi = glXGetVisualFromFBConfig(display, bestFbc);
    std::cout << "Chosen visual ID = 0x" << vi->visualid << "\n";
    std::cout << "Creating Colormap\n";
    XSetWindowAttributes swa;
    Colormap cmap;
    swa.colormap = cmap = XCreateColormap(display,
                                          RootWindow(display, vi->screen),
                                          vi->visual, AllocNone);

    swa.background_pixmap = None;
    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask;

    std::cout << "Creating window\n";
    Window win = XCreateWindow(display, RootWindow(display, vi->screen),
                               0, 0, 100, 100, 0, vi->depth, InputOutput,
                               vi->visual,
                               CWBorderPixel | CWColormap | CWEventMask, &swa);
    if (!win)
    {
        std::cout << "Failed to create window\n";
        return EXIT_FAILURE;
    }

    XFree(vi);
    XStoreName(display, win, "2048");
    std::cout << "Mapping window\n";
    XMapWindow(display, win);

    const char *glxExts = glXQueryExtensionsString(display,
                                                   DefaultScreen(display));

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
        glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

    GLXContext ctx = 0;
    ctxErrorOccured = false;

    int (*oldHandler)(Display *, XErrorEvent *) =
        XSetErrorHandler(&ctxErrorHandler);

    if (!isExtensionSupported(glxExts, "GLX_ARB_create_context") ||
        !glXCreateContextAttribsARB)
    {
        std::cout << "glXCreateContextAttribsARB() not found\n  ... using old-style GLX context\n";
        ctx = glXCreateNewContext(display, bestFbc, GLX_RGBA_TYPE, 0, True);
    }
    else
    {

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

    if (ctxErrorOccured || !ctx)
    {
        std::cout << "Failed to create an OpenGL context\n";
        return EXIT_FAILURE;
    }

    if (!glXIsDirect(display, ctx))
    {
        std::cout << "Indirect GLX rendering context obtained\n";
    } else {
        std::cout << "Direct GLX rendering context obtained\n";
    }

    std::cout << "Making context current\n";
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


    return EXIT_SUCCESS;
}
