/*

WinFea(Window Feather)

A lightweight framework to build light apps :).

Made by: Juan Yaguaro(aka silverhacker)

License: GPL-2.0

*/

#ifndef WINFEA_HPP
#define WINFEA_HPP
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

inline constexpr SDL_InitFlags VIDEO = SDL_INIT_VIDEO;
using win = SDL_Window*;
using render = SDL_Renderer*;

namespace WinFea{
    void Init(int flags);
    render MakeWindow(render& r, win& w, std::string title, int width, int height);

    class RenderableObject {
    public:
        virtual ~RenderableObject() = default;
        virtual void Render(render r) const = 0;
    };

    class WinFeaWindow {
    public:
        void AddObject(RenderableObject* object);
        void Render(render r, RenderableObject& object);
        void RenderAll(render r) const;
        void Loop(win w, render r);
        virtual ~WinFeaWindow() = default;

    private:
        std::vector<RenderableObject*> renderObjects;
        void Shutdown(win w, render r);
    };

    void Render(WinFeaWindow& window, RenderableObject& object);
};

#endif