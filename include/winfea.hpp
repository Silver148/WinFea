/*

WinFea(Window Feather)

A lightweight framework to build light apps :).

Made by: Juan Yaguaro(aka silverhacker)

License: GPL-2.0

*/

#ifndef WINFEA_HPP
#define WINFEA_HPP
#include <SDL3/SDL.h>
#include <string>

#define VIDEO SDL_INIT_VIDEO
#define win SDL_Window*
#define render SDL_Renderer*

namespace WinFea{
    void Init(int flags);
    render MakeWindow(render& r, win& w, std::string title, int width, int height);

    class WinFeaWindow{

        public:
            void Loop(win w, render r);
            virtual void Render(render r);

        private:
            void Shutdown(win w, render r);
    };
};

#endif