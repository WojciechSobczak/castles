#pragma once
#include "sdl_include.hpp"
#include "sdlsmallguards.hpp"
#include "sdlsurface.hpp"
#include "sdltexture.hpp"
#include "sdlwindow.hpp"


namespace sdlwrap {

    class SDLRenderer {
    private:
        SDL_Renderer* renderer{};
    public:
        SDLRenderer(const SDLWindow& window, int index = -1, uint32_t flags = SDL_RENDERER_ACCELERATED);
        ~SDLRenderer();
        
        void clear();
        void present();
        
        void setRenderColor(SDL_Color rgbaColor);
        void setRenderScale(float xScale, float yScale);
        void setRenderScale(float scale);

        void drawFilledSquare(uint32_t x, uint32_t y, uint32_t size);
        void drawEmptySquare(uint32_t x, uint32_t y, uint32_t size);
        void drawTexture(const SDLTexture& texture, uint32_t x, uint32_t y);

        SDLTexture createTexture(const SDLSurface& surface);
        SDL_Renderer* get() const noexcept;
    };
}

