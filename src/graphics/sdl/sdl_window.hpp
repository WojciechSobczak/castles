#pragma once
#include <string>
#include "../application/sdl/sdl_include.hpp"

namespace sdlwrap {
    class SDLWindow {
    private:
        SDL_Window* window{};
    public:
        const std::string windowTitle;

        SDLWindow(
            const char* windowTitle,
            uint32_t width = 800,
            uint32_t height = 600,
            uint32_t flags = SDL_WINDOW_OPENGL,
            uint32_t initXPosition = SDL_WINDOWPOS_UNDEFINED,
            uint32_t initYPosition = SDL_WINDOWPOS_UNDEFINED
        );
        ~SDLWindow();
        
        SDL_Window* get() const noexcept;

        std::pair<uint32_t, uint32_t> getWindowSize() const noexcept;

    };
}