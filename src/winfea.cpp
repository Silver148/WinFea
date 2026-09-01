/*

WinFea(Window Feather)

A lightweight framework to build light apps :).

Made by: Juan Yaguaro(aka silverhacker)

License: GPL-2.0

*/

#include "winfea.hpp"

void WinFea::Init(int flags){
    if(!SDL_Init(static_cast<SDL_InitFlags>(flags))){
        std::cout << "Failed to init SDL: " << SDL_GetError() << std::endl;
        return;
    }
}

render WinFea::MakeWindow(render& r, win& w, std::string title, int width, int height){
    if(!SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &w, &r)){
        std::cout << "Failed to make window: " << SDL_GetError() << std::endl;
    }

    return r;
}

void WinFea::WinFeaWindow::AddObject(RenderableObject* object){
    if(object){
        renderObjects_.push_back(object);
    }
}

void WinFea::WinFeaWindow::Render(render r, RenderableObject& object){
    (void)r;
    AddObject(&object);
}

void WinFea::WinFeaWindow::RenderAll(render r) const{
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);

    for(const auto* object : renderObjects_){
        if(object){
            object->Render(r);
        }
    }

    SDL_RenderPresent(r);
}

void WinFea::WinFeaWindow::Loop(win w, render r){
    SDL_Event e;
    bool running = true;

    while(running){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_EVENT_QUIT){
                running = false;
            }
        }

        this->RenderAll(r);
        SDL_Delay(16); //Sleep CPU for 16 ms
    }

    this->Shutdown(w, r); //Bye bye
}

void WinFea::WinFeaWindow::Shutdown(win w, render r){
    if(w && r){
        SDL_DestroyRenderer(r);
        SDL_DestroyWindow(w);
    }

    SDL_Quit();
}

void WinFea::Render(WinFeaWindow& window, RenderableObject& object){
    window.Render(nullptr, object);
}