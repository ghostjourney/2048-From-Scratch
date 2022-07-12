#pragma once

#include "gfs/window.hpp"
#include "gfs/vertex.hpp"
#include <SDL2/SDL.h>
#include <cstdint>
#include <string>
#include <vector>

class _Window : public gfs::Window {
    private:
        SDL_Window* _win = nullptr;

        //std::string mTitle;
        //double mWidth;
        //double mHeight;
        
    public:
        inline bool Init(void) {_win = SDL_CreateWindow( 
            Window::GetTitle().c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            Window::GetWidth(),
            Window::GetHeight(),
            SDL_WINDOW_SHOWN
        ); return EXIT_SUCCESS;}

        inline SDL_Window* getWinPtr() {return _win;}

        inline void SetTitle(std::string title) {
            Window::SetTitle(title);
            //SDL_SetWindowTitle(_win, title.c_str());
            return;
        }

        inline void Draw(std::vector<gfs::Vertex2D>& vertices) {}
        inline void SetHeightWidth(double height, double width)  {
            SDL_SetWindowSize(_win, width, height );
            Window::SetHeightWidth(height, width);
            
            return;

        }
        inline _Window(std::string title, double _h, double _w){
            Window::SetHeightWidth(_h, _w);
            Window::SetTitle(title);
            Init();
        }

      
};