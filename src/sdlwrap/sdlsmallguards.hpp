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
        ~SDLLifetimeGuard() {
            SDL_Quit();
        }
    };

    class SDLTTFLifetimeGuard {
    public:
        SDLTTFLifetimeGuard() {
            TTF_Init();
        }
        ~SDLTTFLifetimeGuard() {
            TTF_Quit();
        }
    };

    class SDLSurface {
    private:
        SDL_Surface* surface{};
    public:
        SDLSurface(SDL_Surface* surface) : surface(surface) {}
        SDLSurface(SDLSurface&& other) {
            this->surface = other.surface;
            other.surface = nullptr;
        }
        ~SDLSurface() {
            SDL_FreeSurface(this->surface);
        }

        SDL_Surface* get() const noexcept {
            return this->surface;
        }

    };


    class SDLTexture {
    private:
        SDL_Texture* texture{};
    public:
        SDLTexture(SDL_Texture* texture) : texture(texture) {}
        SDLTexture(SDLTexture&& other) {
            this->texture = other.texture;
            other.texture = nullptr;
        }
        ~SDLTexture() {
            SDL_DestroyTexture(this->texture);
        }

        SDL_Texture* get() const noexcept {
            return this->texture;
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
        SDLTTFFont(SDLTTFFont&& other) {
            this->font = other.font;
            other.font = nullptr;
        }
        ~SDLTTFFont() {
            TTF_CloseFont(this->font);
        }

        TTF_Font* get() const noexcept {
            return this->font;
        }

    };
}
