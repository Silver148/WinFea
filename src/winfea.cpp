/*
WinFea(Window Feather)
A lightweight framework to build light apps :).
Made by: Juan Yaguaro(aka silverhacker)
License: GPL-2.0
*/

#include "winfea.hpp"
#include "winfea_events.hpp"

void WinFea::Init(int flags){
    if(!SDL_Init(static_cast<SDL_InitFlags>(flags))){
        std::cout << "Failed to init SDL: " << SDL_GetError() << std::endl;
        return;
    }

    if(flags & AUDIO){
        if(MIX_Init() == 0){
            std::cout << "Failed to init SDL_mixer: " << SDL_GetError() << std::endl;
            return;
        }
    }

    if(!TTF_Init()){
        std::cout << "Failed to init SDL_ttf: " << SDL_GetError() << std::endl;
        return;
    }
}

void WinFea::Quit(){
    TTF_Quit();
    MIX_Quit();
    SDL_Quit();
}

render WinFea::MakeWindow(render& r, win& w, std::string title, int width, int height){
    if(!SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &w, &r)){
        std::cout << "Failed to make window: " << SDL_GetError() << std::endl;
        r = nullptr;
        w = nullptr;
        return nullptr;
    }

    return r;
}

WinFea::WinFeaWindow::~WinFeaWindow() {
    Shutdown();
}

void WinFea::WinFeaWindow::AddObject(RenderableObject* object){
    if(object){
        renderObjects.push_back(object);
    }
}

void WinFea::WinFeaWindow::Render(render r, RenderableObject& object){
    (void)r;
    AddObject(&object);
}

void WinFea::WinFeaWindow::RenderAll(render r) const{
    if(!r){
        return;
    }

    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);

    for(const auto* object : renderObjects){
        if(object){
            object->Render(r);
        }
    }

    SDL_RenderPresent(r);
}

void WinFea::WinFeaWindow::Loop(win w, render r, WinFeaEvent* eventHandler){
    if(!w || !r){
        std::cerr << "Window and renderer are not initialized. Skipping main loop." << std::endl;
        return;
    }

    window = w;
    renderer = r;

    WinFeaEvent defaultEventHandler;
    WinFeaEvent* activeEventHandler = eventHandler ? eventHandler : &defaultEventHandler;

    while(activeEventHandler->running){
        activeEventHandler->ManageEvents();
        activeEventHandler->Update();

        if(!activeEventHandler->running){
            break;
        }

        this->RenderAll(renderer);
        SDL_Delay(16);
    }

    this->Shutdown();
}

void WinFea::WinFeaWindow::Shutdown(){
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void WinFea::Render(WinFeaWindow& window, RenderableObject& object){
    window.Render(nullptr, object);
}