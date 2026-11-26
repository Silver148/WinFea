#ifndef WINFEA_HELPERS_HPP
#define WINFEA_HELPERS_HPP
#include "winfea.hpp"

class WinFeaRectangle : public WinFea::RenderableObject{
public:
    WinFeaRectangle(int width, int height, int rounding = 0)
        : width_(width), height_(height), rounding_(rounding > 0 ? rounding : 0) {}

    ~WinFeaRectangle() override = default;

    void Render(render renderer) const override {
        draw(renderer, x_, y_);
    }

    void draw(SDL_Renderer* renderer, int x, int y) const;

    void SetPosition(int x, int y) {
        x_ = x;
        y_ = y;
    }

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    int getRounding() const { return rounding_; }

private:
    int width_;
    int height_;
    int rounding_;
    int x_ = 0;
    int y_ = 0;
};

#endif