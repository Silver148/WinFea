#include "winfea_helpers.hpp"

void WinFeaRectangle::draw(SDL_Renderer* renderer, int x, int y) const {
    if (!renderer || width_ <= 0 || height_ <= 0) {
        return;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //By default for the moment

    const SDL_FRect rect = {
        static_cast<float>(x), static_cast<float>(y),
        static_cast<float>(width_), static_cast<float>(height_)
    };
    if (rounding_ <= 0) {
        SDL_RenderRect(renderer, &rect);
        return;
    }

    const int halfWidth = width_ / 2 + width_ % 2;
    const int halfHeight = height_ / 2 + height_ % 2;
    const int radius = rounding_ < halfWidth
        ? (rounding_ < halfHeight ? rounding_ : halfHeight)
        : (halfWidth < halfHeight ? halfWidth : halfHeight);
    const int right = x + width_ - 1;
    const int bottom = y + height_ - 1;

    SDL_RenderLine(renderer, static_cast<float>(x + radius), static_cast<float>(y),
                    static_cast<float>(right - radius), static_cast<float>(y));
    SDL_RenderLine(renderer, static_cast<float>(x + radius), static_cast<float>(bottom),
                    static_cast<float>(right - radius), static_cast<float>(bottom));
    SDL_RenderLine(renderer, static_cast<float>(x), static_cast<float>(y + radius),
                    static_cast<float>(x), static_cast<float>(bottom - radius));
    SDL_RenderLine(renderer, static_cast<float>(right), static_cast<float>(y + radius),
                    static_cast<float>(right), static_cast<float>(bottom - radius));

    const int centerX[4] = { x + radius, right - radius, x + radius, right - radius };
    const int centerY[4] = { y + radius, y + radius, bottom - radius, bottom - radius };
    const int directionX[4] = { -1, 1, -1, 1 };
    const int directionY[4] = { -1, -1, 1, 1 };
    int circleX = radius;
    int circleY = 0;
    int error = 1 - radius;

    while (circleX >= circleY) {
        for (int corner = 0; corner < 4; ++corner) {
            SDL_RenderPoint(renderer,
                static_cast<float>(centerX[corner] + directionX[corner] * circleX),
                static_cast<float>(centerY[corner] + directionY[corner] * circleY));
            SDL_RenderPoint(renderer,
                static_cast<float>(centerX[corner] + directionX[corner] * circleY),
                static_cast<float>(centerY[corner] + directionY[corner] * circleX));
        }
        ++circleY;
        if (error < 0) {
            error += 2 * circleY + 1;
        } else {
            --circleX;
            error += 2 * (circleY - circleX) + 1;
        }
    }
}