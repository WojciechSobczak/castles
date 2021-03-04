#pragma once
#include "sdl_include.hpp"

namespace sdlwrap {
    class SDLSurface {
    private:
        SDL_Surface* surface{};
    public:
        SDLSurface(SDL_Surface* surface);
        SDLSurface(SDLSurface&& other) noexcept;
        ~SDLSurface() noexcept;
        SDL_Surface* get() const noexcept;
    };
}

