#include "winfea_images.hpp"

SDL_Texture* WinFeaImage::ShowImage(render r, std::string path, float x, float y){
    if(texture_){
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }

    texture_ = IMG_LoadTexture(r, path.c_str());
    rect_ = {0.0f, 0.0f, 0.0f, 0.0f};

    if(!texture_){
        std::cout << "Failed to load image '" << path << "': " << SDL_GetError() << std::endl;
        return nullptr;
    }

    float tw = 0.0f;
    float th = 0.0f;

    if(SDL_GetTextureSize(texture_, &tw, &th)){
        SetRect(x, y, tw, th);
    }

    return texture_;
}

SDL_Texture* WinFeaImage::RedimensionTexture(float w, float h){
    rect_.w = w;
    rect_.h = h;
    return texture_;
}