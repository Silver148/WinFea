#ifndef WINFEA_IMAGES_HPP
#define WINFEA_IMAGES_HPP
#include "winfea.hpp"

class WinFeaImage : public WinFea::RenderableObject {
private:
    SDL_Texture* texture_ = nullptr;
    SDL_FRect rect_ = {0.0f, 0.0f, 0.0f, 0.0f};

public:
    ~WinFeaImage() override {
        if(texture_){
            SDL_DestroyTexture(texture_);
            texture_ = nullptr;
        }
    }

    void Render(render r) const override {
        if(texture_){
            SDL_RenderTexture(r, texture_, nullptr, &rect_);
        }
    }

    SDL_Texture* ShowImage(render r, std::string path, float x, float y);
    SDL_Texture* RedimensionTexture(float w, float h);
    SDL_Texture* GetTexture() const { return texture_; }

    void SetRect(float x, float y, float w, float h) {
        rect_.x = x;
        rect_.y = y;
        rect_.w = w;
        rect_.h = h;
    }
};

#endif