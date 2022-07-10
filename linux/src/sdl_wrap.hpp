#pragma once
#include <SDL2/SDL.h>
#include <cstdint>

inline bool _isSDL() {
    if (SDL_Init( SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " 
        << SDL_GetError() << "\n";
        return EXIT_FAILURE; 

    } else { return EXIT_SUCCESS; }
}



