#pragma once
#include "sdlwrap.hpp"
#include <string>

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
        ) : windowTitle(windowTitle) {
            this->window = SDL_CreateWindow(
                this->windowTitle.c_str(),
                initXPosition,
                initYPosition,
                width,
                height,
                flags
            );

            if (this->window == nullptr) {
                throw SDLException("SDL_CreateWindow() failed");
            }
        }

        ~SDLWindow() {
            SDL_DestroyWindow(window);
        }

        SDL_Window* get() const noexcept {
            return this->window;
        }

        std::pair<uint32_t, uint32_t> getWindowSize() const noexcept {
            int width = 0;
            int height = 0;
            SDL_GetWindowSize(this->window, &width, &height);
            return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
        }
    };
}