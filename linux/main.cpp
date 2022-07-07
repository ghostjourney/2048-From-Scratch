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
        std::cout << "Failed to open X display\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}
