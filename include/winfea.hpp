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
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>

inline constexpr SDL_InitFlags VIDEO = SDL_INIT_VIDEO;
inline constexpr SDL_InitFlags AUDIO = SDL_INIT_AUDIO;

using win = SDL_Window*;
using render = SDL_Renderer*;

class WinFeaEvent;

namespace WinFea{
    void Init(int flags);
    void Quit();
    render MakeWindow(render& r, win& w, std::string title, int width, int height);

    class RenderableObject {
    public:
        virtual ~RenderableObject() = default;
        virtual void Render(render r) const = 0;
    };

    class Context {
    public:
        Context(int flags) {
            Init(flags);
        }
        
        ~Context() {
            Quit();
        }

        Context(const Context&) = delete;
        Context& operator=(const Context&) = delete;
    };

    class WinFeaWindow {
    public:
        WinFeaWindow() = default;
        virtual ~WinFeaWindow();

        void AddObject(RenderableObject* object);
        void Render(render r, RenderableObject& object);
        void RenderAll(render r) const;
        void Loop(win w, render r, WinFeaEvent* eventHandler = nullptr);
        void Shutdown();

    private:
        std::vector<RenderableObject*> renderObjects;
        win window = nullptr;
        render renderer = nullptr;
    };

    void Render(WinFeaWindow& window, RenderableObject& object);
};

#endif