#pragma once 
#include <string>
#include "sdl_include.hpp"

namespace sdlwrap {
    class SDLException {
    private:
        const std::string message;
    public:
        SDLException(const std::string& message) : message(message + " | SDLMessage: " + SDL_GetError()) {}

        const std::string& getMessage() const noexcept {
            return this->message;
        }
    };

    class SDLLifetimeGuard {
    public:
        SDLLifetimeGuard() {
            SDL_SetMainReady();
            if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                throw SDLException("SDL_Init(SDL_INIT_VIDEO) failed");
            }
        }
        ~SDLLifetimeGuard() noexcept {
            SDL_Quit();
        }
    };

    class SDLTTFLifetimeGuard {
    public:
        SDLTTFLifetimeGuard() {
            if (TTF_Init() != 0) {
                throw SDLException("TTF_Init() failed");
            }
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

        SDLTTFFont(SDLTTFFont&& other) noexcept {
            this->font = other.font;
            other.font = nullptr;
        }
        SDLTTFFont& operator=(SDLTTFFont&& other) noexcept {
            this->font = other.font;
            other.font = nullptr;
        }

        ~SDLTTFFont() noexcept {
            if (this->font != nullptr) {
                TTF_CloseFont(this->font);
            }
        }

        TTF_Font* get() const noexcept {
            return this->font;
        }
    };

    class SDLRWops {
    private:
        SDL_RWops* stream{};
    public:
        SDLRWops(SDL_RWops* stream) : stream(stream) {}

        SDLRWops(SDLRWops&& other) noexcept {
            this->stream = other.stream;
            other.stream = nullptr;
        }
        SDLRWops& operator=(SDLRWops&& other) noexcept {
            this->stream = other.stream;
            other.stream = nullptr;
        }

        ~SDLRWops() noexcept {
            if (this->stream != nullptr) {
                SDL_RWclose(this->stream);
            }
        }

        SDL_RWops* get() const noexcept {
            return this->stream;
        }
    };
}
