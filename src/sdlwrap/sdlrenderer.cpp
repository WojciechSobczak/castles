#include "sdlrenderer.hpp"
#include <string>

namespace sdlwrap {
    SDLRenderer::SDLRenderer(const SDLWindow& window, int index, uint32_t flags) {
        this->renderer = SDL_CreateRenderer(window.get(), index, flags);
        if (this->renderer == nullptr) {
            throw SDLException("SDL_CreateRenderer() failed");
        }
    };

    SDLRenderer::~SDLRenderer() {
        SDL_DestroyRenderer(this->renderer);
    }

    void SDLRenderer::setRenderColor(SDL_Color rgbaColor) {
        int result = SDL_SetRenderDrawColor(this->renderer, rgbaColor.r, rgbaColor.g, rgbaColor.b, rgbaColor.a);
        if (result == -1) {
            throw SDLException("SDL_SetRenderDrawColor() failed");
        }
    }

    void SDLRenderer::setRenderScale(float xScale, float yScale) {
        int result = SDL_RenderSetScale(this->renderer, xScale, yScale);
        if (result == -1) {
            throw SDLException("SDL_RenderSetScale() failed");
        }
    }

    void SDLRenderer::setRenderScale(float scale) {
        this->setRenderScale(scale, scale);
    }

    void SDLRenderer::clear() {
        setRenderColor({ .r = 0, .g = 0, .b = 0, .a = 0 });
        int result = SDL_RenderClear(this->renderer);
        if (result == -1) {
            throw SDLException("SDL_RenderClear() failed");
        }
    }

    void SDLRenderer::present() {
        SDL_RenderPresent(this->renderer);
    }

    void SDLRenderer::enableDrawBlendMode() {
        int result = SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
        if (result == -1) {
            throw SDLException("SDL_SetRenderDrawBlendMode() failed");
        }
    }

    void SDLRenderer::drawFilledRectangle(int32_t x, int32_t y, uint32_t width, uint32_t height) {
        SDL_Rect rect{
            .x = x,
            .y = y,
            .w = static_cast<int>(width),
            .h = static_cast<int>(height)
        };
        int result = SDL_RenderFillRect(this->renderer, &rect);
        if (result == -1) {
            throw SDLException("SDL_RenderFillRect() failed");
        }
    }

    void SDLRenderer::drawEmptyRectangle(int32_t x, int32_t y, uint32_t width, uint32_t height) {
        SDL_Rect rect{
            .x = x,
            .y = y,
            .w = static_cast<int>(width),
            .h = static_cast<int>(height)
        };
        int result = SDL_RenderDrawRect(this->renderer, &rect);
        if (result == -1) {
            throw SDLException("SDL_RenderDrawRect() failed");
        }
    }

    void SDLRenderer::drawFilledSquare(int32_t x, int32_t y, uint32_t size) {
        this->drawFilledRectangle(x, y, size, size);
    }

    void SDLRenderer::drawEmptySquare(int32_t x, int32_t y, uint32_t size) {
        this->drawEmptyRectangle(x, y, size, size);
    }

    SDLTexture SDLRenderer::createTexture(const SDLSurface& surface) {
        SDLTexture texture{ SDL_CreateTextureFromSurface(this->renderer, surface.get()) };
        if (texture.get() == nullptr) {
            throw SDLException("SDL_CreateTextureFromSurface() failed");
        }
        return texture;
    }

    void SDLRenderer::drawTexture(const SDLTexture& texture, int32_t x, int32_t y, uint32_t width, uint32_t height) {
        SDL_Rect rect{
            .x = x,
            .y = y,
            .w = static_cast<int>(width),
            .h = static_cast<int>(height)
        };
        int result = SDL_RenderCopy(this->renderer, texture.get(), nullptr, &rect);
        if (result != 0) {
            throw SDLException("SDL_RenderCopy() failed");
        }
    }

    void SDLRenderer::drawTexture(const SDLTexture& texture, int32_t x, int32_t y) {
        this->drawTexture(texture, x, y, texture.getWidth(), texture.getHeight());
    }
    void SDLRenderer::drawTexture(const SDLTexture& texture, int32_t x, int32_t y, float xScale, float yScale) {
        this->drawTexture(texture, x, y, static_cast<uint32_t>(texture.getWidth() * xScale), static_cast<uint32_t>(texture.getHeight() * yScale));
    }

    SDL_Renderer* SDLRenderer::get() const noexcept {
        return this->renderer;
    }
}

