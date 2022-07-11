#pragma once

#include <SDL.h>

#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL/SDL_opengl.h>
#include <string>



GLuint gProgramID           = 0;
GLint  gVertexPos2DLocation = -1;
GLuint gVBO                 = 0;
GLuint gIBO                 = 0;

SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );


void inline printProgramLog ( GLunit program );
void inline printShaderLog  ( GLuint shader  );

inline bool isGLCtx ( SDL_Window* _w ) {
    if (_w == nullptr){
        std::cout << "OpenGL context could not be created! SDL Error: " <<
        SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

inline void isInitGL () {
    auto glewExperimental = GL_TRUE;
    GLenum glewError      = glewInit();
    
    if (glewError != GLEW_OK ) {
        std::cout << "Error initializing GLEW!\n " <<
        glewGetErrorString( glewError );
    }

    if ( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
        std::cout << "Warning: Unable to set VSync! SDL Error: \n" <<
        SDL_GetError() << "\n";
    }
    return;
}

inline bool initGL() {
    bool success = true;
    gProgramID = glCreateProgram();
}
