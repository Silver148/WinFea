/*

WinFea(Window Feather)

A lightweight framework to build light apps :).

Made by: Juan Yaguaro(aka silverhacker)

License: GPL-2.0

*/

#ifndef WINFEA_TEXT_HPP
#define WINFEA_TEXT_HPP
#include "winfea.hpp"

#define BLACK SDL_Color{0, 0, 0, 255}
#define WHITE SDL_Color{255, 255, 255, 255}
#define RED SDL_Color{255, 0, 0, 255}
#define CYAN SDL_Color{0, 255, 255, 255}
#define GREEN SDL_Color{0, 255, 0, 255}
#define PINK SDL_Color{255, 0, 255, 255}
#define BLUE SDL_Color{0, 0, 255, 255}
#define YELLOW SDL_Color{255, 255, 0, 255}
#define GRAY SDL_Color{128, 128, 128, 255}
#define ORANGE SDL_Color{255, 165, 0, 255}
#define PURPLE SDL_Color{128, 0, 128, 255}

class WinFeaText : public WinFea::RenderableObject {

private:
    SDL_Surface* surf = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_FRect rect = {0.0f, 0.0f, 0.0f, 0.0f};
    TTF_Font* font = nullptr;

public:
    ~WinFeaText() override {
        if(texture){
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
        if(surf){
            SDL_DestroySurface(surf);
            surf = nullptr;
        }
        if(font){
            TTF_CloseFont(font);
            font = nullptr;
        }
    }

    void Render(render r) const override {
        if(texture){
            SDL_RenderTexture(r, texture, nullptr, &rect);
        }
    }

    void LoadFont(std::string path, int size);
    void ShowText(render r, std::string text, SDL_Color color, float x, float y);

    void SetRect(float x, float y, float w, float h) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }
};

#endif