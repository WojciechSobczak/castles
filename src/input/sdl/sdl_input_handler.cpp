#include "sdl_input_handler.hpp"
#include "../../application/sdl/sdl_include.hpp"

#include <spdlog/spdlog.h>

bool SDLInputHandler::handleInputEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            return true;
        }
        if (event.type == SDL_MOUSEWHEEL) {
            this->onMouseWheel(event.wheel.y);
        }
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            this->sdlKeyboardState = SDL_GetKeyboardState(NULL);
        }
        if (event.type == SDL_KEYDOWN) {
            this->onKeyPressed();
        }
    }
    return false;
}

void SDLInputHandler::setOnMouseWheel(std::function<void(int32_t)> onMouseWheel) {
    this->onMouseWheel = onMouseWheel;
}

void SDLInputHandler::setOnKeyPressed(std::function<void()> onKeyPressed) {
    this->onKeyPressed = onKeyPressed;
}

bool SDLInputHandler::isLeftCtrlPressed() const noexcept {
    return this->sdlKeyboardState[SDL_SCANCODE_LCTRL] == 1;
}

bool SDLInputHandler::isDPressed() const noexcept {
    return this->sdlKeyboardState[SDL_SCANCODE_D] == 1;
}
