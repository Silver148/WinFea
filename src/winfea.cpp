#include "winfea.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SDL3/SDL.h>

void WinFea::Init(int flags){

    if(!SDL_Init(flags)){
        std::cout << "Failed to init SDL:" << SDL_GetError() << std::endl;
    }
}

render WinFea::MakeWindow(render& r, win& w, std::string title, int width, int height){

    if(!SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &w, &r)){
        std::cout << "Failed to make window:" << SDL_GetError() << std::endl;
    }

    return r; 
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

        this->Render(r);
        SDL_Delay(16); //Sleep CPU for 16 ms
    }

    this->Shutdown(w, r); //Bye bye
}

void WinFea::WinFeaWindow::Render(render r){

    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    SDL_RenderClear(r);
    SDL_RenderPresent(r);
}

void WinFea::WinFeaWindow::Shutdown(win w, render r){
    if(w && r){
        SDL_DestroyRenderer(r);
        SDL_DestroyWindow(w);
    }

    SDL_Quit();
}