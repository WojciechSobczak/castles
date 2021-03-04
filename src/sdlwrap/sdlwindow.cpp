#include "sdl_include.hpp"
#include "sdlwindow.hpp"
#include "sdlsmallguards.hpp"


namespace sdlwrap {
    SDLWindow::SDLWindow(
        const char* windowTitle,
        uint32_t width,
        uint32_t height,
        uint32_t flags,
        uint32_t initXPosition,
        uint32_t initYPosition
    ) : windowTitle(windowTitle) 
    {
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

    SDLWindow::~SDLWindow() {
        SDL_DestroyWindow(window);
    }

    SDL_Window* SDLWindow::get() const noexcept {
        return this->window;
    }

    std::pair<uint32_t, uint32_t> SDLWindow::getWindowSize() const noexcept {
        int width = 0;
        int height = 0;
        SDL_GetWindowSize(this->window, &width, &height);
        return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
    }
}
