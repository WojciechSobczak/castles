#pragma once 
#include "sdlwrap.hpp"
#include <string>

namespace sdlwrap {
    class SDLException {
    private:
        const std::string message;
    public:
        SDLException(const std::string& message) : message(message + " | SDLMessage: " + SDL_GetError()) {}

        const std::string& getMessage() {
            return this->message;
        }
    };

    class SDLLifetimeGuard {
    public:
        SDLLifetimeGuard() {
            SDL_Init(SDL_INIT_VIDEO);
        }
        ~SDLLifetimeGuard() noexcept {
            SDL_Quit();
        }
    };

    class SDLTTFLifetimeGuard {
    public:
        SDLTTFLifetimeGuard() {
            TTF_Init();
        }
        ~SDLTTFLifetimeGuard() noexcept {
            TTF_Quit();
        }
    };

    class SDLTTFFont {
    private:
        TTF_Font* font{};
    public:
        SDLTTFFont(TTF_Font* font) : font(font) {}
        SDLTTFFont(const std::string& path, uint32_t size) {
            this->font = TTF_OpenFont(path.c_str(), size);
            if (this->font == nullptr) {
                throw SDLException("TTF_OpenFont() failed");
            }
        }
        SDLTTFFont(SDLTTFFont&& other) noexcept {
            this->font = other.font;
            other.font = nullptr;
        }
        ~SDLTTFFont() noexcept {
            TTF_CloseFont(this->font);
        }

        TTF_Font* get() const noexcept {
            return this->font;
        }

    };
}
