/*

WinFea(Window Feather)

A lightweight framework to build light apps :).

Made by: Juan Yaguaro(aka silverhacker)

License: GPL-2.0

*/

#ifndef WINFEA_IMAGES_HPP
#define WINFEA_IMAGES_HPP
#include "winfea.hpp"

class WinFeaImage : public WinFea::RenderableObject {
private:
    SDL_Texture* texture = nullptr;
    SDL_FRect rect = {0.0f, 0.0f, 0.0f, 0.0f};

public:
    ~WinFeaImage() override {
        if(texture){
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }

    void Render(render r) const override {
        if(texture){
            SDL_RenderTexture(r, texture, nullptr, &rect);
        }
    }

    SDL_Texture* LoadImage(render r, std::string path, float x, float y);
    SDL_Texture* RedimensionTexture(float w, float h);
    SDL_Texture* GetTexture() const { return texture; }

    void SetRect(float x, float y, float w, float h) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }
};

#endif