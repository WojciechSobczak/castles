#pragma once
#include "../../sdl/sdl_include.hpp"

namespace sdlwrap {
    class SDLTexture {
    private:
        SDL_Texture* texture{};

        uint32_t width{};
        uint32_t height{};

        void loadProperties();
    public:
        SDLTexture(SDL_Texture* texture);
        SDLTexture(SDLTexture&& other) noexcept;
        ~SDLTexture() noexcept;
        SDL_Texture* get() const noexcept;

        uint32_t getWidth() const noexcept;
        uint32_t getHeight() const noexcept;

        void rescale(float scaleFactor);
    };
}
