#pragma once

#include <SDL.h>

#include <GL/glu.h>
#include <SDL/SDL_opengl.h>
#include <string>



GLuint gProgramID           = 0;
GLint  gVertexPos2DLocation = -1;
GLuint gVBO                 = 0;
GLuint gIBO                 = 0;



inline bool initGL() {
    bool success    = true;
    GLenum error    = GL_NO_ERROR;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    error = glGetError();
    if ( error != GL_NO_ERROR ) {
        std::cout << "Error initializing OpenGL! " <<
        gluErrorString( error ) << "\n";
        success = false;
    }

    glMatrixMode ( GL_MODELVIEW );
    glLoadIdentity();

    error = glGetError();
    if ( error != GL_NO_ERROR ) {
        std::cout << "Error initializing OpenGL! " <<
        gluErrorString( error ) << "\n";
        success = false;
    }
    
}

inline bool init(SDL_Window* _w, SDL_GLContext* _gl) {
    if (_w == nullptr) {
        std::cout << "Window could not be created! SDL_GetError: " <<
        SDL_GetError() << "\n";
        return EXIT_FAILURE;
    } else {
        *_gl = SDL_GL_CreateContext(_w);
        if (*_gl == nullptr) {
            std::cout << "OpenGL context could not be created! SDL Error: " <<
            SDL_GetError() << "\n";
        } else {
            if (SDL_GL_SetSwapInterval( 1 ) < 0) {
                std::cout << "Warning: Unable to set VSync! SDL Error: " <<
                SDL_GetError();
            } else {
                return EXIT_SUCCESS;
            }
        }
    }
    return EXIT_SUCCESS;
}







