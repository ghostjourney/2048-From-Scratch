#include <iostream>

#include <stdio.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <unistd.h>


static bool isExtensionSupported( const char *extlist, const char *extension ){
    const char *start;
    const char *where, *terminator;

    where = strchr( extension, ' ' );
    if ( where || *extension == '\0' )
        return false;

    for (start=extlist;;) {
        where = strstr( start, extension );
        if (!where)
            break;
        terminator = where + strlen( extension );

        if ( where == start || *( where - 1 ) == ' ' )
            if ( *terminator == ' ' || *terminator == '\0' )
                return true;

        start = terminator;
    }
    return false;
}

static bool ctxErrorOccured = false;
static int ctxErrorHandler( Display *dpy, XErrorEvent *ev ) {
    ctxErrorOccured = true;
    return 0;
}

int main(int argc, char* argv[]) {
    
    Display *display = XOpenDisplay(nullptr);
    //sleep(3);

    if (!display){
        std::cout << "Failed to open X display.\n";
        return EXIT_FAILURE;
    }

    static int visual_attribs[] = 
    {
        GLX_X_RENDERABLE    , True,
        GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
        GLX_RENDER_TYPE     , GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
        GLX_RED_SIZE        , 8,
        GLX_GREEN_SIZE      , 8,
        GLX_BLUE_SIZE       , 8,
        GLX_ALPHA_SIZE      , 8,
        GLX_DEPTH_SIZE      , 24,
        GLX_STENCIL_SIZE    , 8,
        GLX_DOUBLEBUFFER    , True,
        None
    };

    int glx_major, glx_minor;

    if ( !glXQueryVersion ( display, &glx_major, &glx_minor ) ||
    ( ( glx_major == 1) && (glx_minor < 3 ) ) || ( glx_major < 1 ) ) {

        std::cout << "Invalid GLX version.\n";
        return EXIT_FAILURE;
    }

    std::cout << "Getting matching framebuffer config.\n";
    int fbcount;

    GLXFBConfig* fbc = glXChooseFBConfig(display,
                            DefaultScreen(display),
                            visual_attribs,
                            &fbcount);
    
    if (!fbc) {
        std::cout << "Failed to retrieve a framebuffer config.\n";
        return EXIT_FAILURE;
    }

    std::cout << "Found " << fbcount << " matching FB configs.\n";
    std::cout << "Getting XVisualInfos\n";

    int best_fbc            = -1,
        worst_fbc           = -1,
        best_num_samp       = -1,
        worst_num_samp      = 999;
    
    int i;
    for ( i = 0; i < fbcount; ++i ) {
        XVisualInfo *vi = glXGetVisualFromFBConfig( display, fbc[i] );
        if ( vi ) {
            int samp_buf, samples;
            glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
            glXGetFBConfigAttrib( display, fbc[i], GLX_SAMPLES,        &samples  );

            std::cout << "  Matching fbconfig " 
                      << i 
                      << ", visual ID 0x" 
                      << vi -> visualid 
                      << "2x: SAMPLE_BUFFERS = "
                      << samp_buf
                      << ", SAMPLES = "
                      << samples <<"\n";
            
            if (best_fbc < 0 || samp_buf && samples > best_num_samp )
                best_fbc = i, best_num_samp = samples
        }
    }


    return EXIT_SUCCESS;

}
