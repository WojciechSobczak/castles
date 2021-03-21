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
        void enableDrawBlendMode();
        
        void setRenderColor(SDL_Color rgbaColor);
        void setRenderScale(float xScale, float yScale);
        void setRenderScale(float scale);

        void drawFilledRectangle(int32_t x, int32_t y, uint32_t width, uint32_t height);
        void drawEmptyRectangle(int32_t x, int32_t y, uint32_t width, uint32_t height);

        void drawFilledSquare(int32_t x, int32_t y, uint32_t size);
        void drawEmptySquare(int32_t x, int32_t y, uint32_t size);

        void drawTexture(const SDLTexture& texture, int32_t x, int32_t y);
        void drawTexture(const SDLTexture& texture, int32_t x, int32_t y, float xScale, float yScale);
        void drawTexture(const SDLTexture& texture, int32_t x, int32_t y, uint32_t width, uint32_t height);

        SDLTexture createTexture(const SDLSurface& surface);
        SDL_Renderer* get() const noexcept;
    };
}

