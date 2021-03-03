#pragma once
#include "sdl_include.hpp"
#include "sdlwindow.hpp"

namespace sdlwrap {
    class SDLRenderer {
    private:
        SDL_Renderer* renderer{};
    public:
        SDLRenderer(const SDLWindow& window, int index = -1, uint32_t flags = SDL_RENDERER_ACCELERATED);
        ~SDLRenderer();
        void setRenderColor(SDL_Color rgbaColor);
        void clear();
        void present();
        void drawSquare(uint32_t x, uint32_t y, uint32_t size);
        SDLTexture createTexture(const SDLSurface& surface);
        void drawTexture(const SDLTexture& texture, uint32_t x, uint32_t y);

        SDL_Renderer* get() const noexcept;
    };
}

