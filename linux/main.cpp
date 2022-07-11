
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <SDL2/SDL.h>
#include "src/sdl_win.hpp"
#include "src/sdl_wrap.hpp"
#include "src/sdl_gl.hpp"
#include <GL/gl.h>
#include <GL/glx.h>

//#include "gfs/window.hpp"
//#include "src/Xwindow.hpp"


const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]){
    //std::cout << " ghost is a necromancer";

    if ( _isSDL() )
        return EXIT_FAILURE;
    
    _Window win( "2048",SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Surface *win_surface = SDL_GetWindowSurface(win.getWinPtr());
    SDL_FillRect(&*win_surface, nullptr, SDL_MapRGB(win_surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(win.getWinPtr());
    //SDL_Delay(3000);
    
    if (!isGLCtx(win.getWinPtr())) {
        return EXIT_FAILURE;
    } 


    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // events go here
        SDL_UpdateWindowSurface(win.getWinPtr());
        //
        while (SDL_PollEvent(&e ) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }



    SDL_DestroyWindow(win.getWinPtr());
    SDL_Quit();

    return EXIT_SUCCESS;
}
