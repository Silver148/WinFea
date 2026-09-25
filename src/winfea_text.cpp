/*
WinFea(Window Feather)
A lightweight framework to build light apps :).
Made by: Juan Yaguaro(aka silverhacker)
License: GPL-2.0
*/

#include "winfea_text.hpp"

void WinFeaText::LoadFont(std::string path, int size){

    if(font){
        TTF_CloseFont(font);
        font = nullptr;
    }

    font = TTF_OpenFont(path.c_str(), size);

    if(!font){
        std::cout << "Failed to load font '" << path << "': " << SDL_GetError() << std::endl;
        return;
    }
}

void WinFeaText::ShowText(render r, std::string text, SDL_Color color, float x, float y){

    if(!r){
        std::cerr << "Renderer is null. Cannot render text." << std::endl;
        return;
    }

    if(!font){
        std::cout << "Font not loaded. Please load a font before showing text." << std::endl;
        return;
    }

    if (text.empty()) {
        return;
    }

    surf = TTF_RenderText_Blended(font, text.c_str(), static_cast<int>(text.size()), color);
    if(!surf){
        std::cerr << "Failed to render text: " << SDL_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(r, surf);

    if(surf){
        SDL_DestroySurface(surf);
        surf = nullptr;
    }

    if (!texture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        return;
    }

    float tw = 0.0f, th = 0.0f;
    
    if(SDL_GetTextureSize(texture, &tw, &th)){
        SetRect(x, y, tw, th);
    }
}
