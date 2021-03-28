#include "sdl_surface.hpp"


namespace sdlwrap {

    SDLSurface::SDLSurface(SDL_Surface* surface) : surface(surface) {}

    SDLSurface::SDLSurface(SDLSurface&& other) noexcept {
        this->surface = other.surface;
        other.surface = nullptr;
    }

    SDLSurface::~SDLSurface() noexcept {
        SDL_FreeSurface(this->surface);
    }

    SDL_Surface* SDLSurface::get() const noexcept {
        return this->surface;
    }
}