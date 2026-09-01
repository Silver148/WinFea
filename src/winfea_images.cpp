#include "winfea_images.hpp"

SDL_Texture* WinFeaImage::ShowImage(render r, std::string path, float x, float y){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    texture = IMG_LoadTexture(r, path.c_str());
    rect = {0.0f, 0.0f, 0.0f, 0.0f};

    if(!texture){
        std::cout << "Failed to load image '" << path << "': " << SDL_GetError() << std::endl;
        return nullptr;
    }

    float tw = 0.0f;
    float th = 0.0f;

    if(SDL_GetTextureSize(texture, &tw, &th)){
        SetRect(x, y, tw, th);
    }

    return texture;
}

SDL_Texture* WinFeaImage::RedimensionTexture(float w, float h){
    rect.w = w;
    rect.h = h;
    return texture;
}