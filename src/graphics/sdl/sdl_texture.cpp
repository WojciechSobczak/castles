#include "sdl_texture.hpp"
#include "../../sdl/sdl_small_guards.hpp"

namespace sdlwrap {
    SDLTexture::SDLTexture(SDL_Texture* texture) : texture(texture) {
        loadProperties();
    }

    SDLTexture::SDLTexture(SDLTexture&& other) noexcept {
        this->texture = other.texture;
        other.texture = nullptr;
        loadProperties();
    }
    SDLTexture::~SDLTexture() noexcept {
        SDL_DestroyTexture(this->texture);
    }

    SDL_Texture* SDLTexture::get() const noexcept {
        return this->texture;
    }

    void SDLTexture::loadProperties() {
        int loadedWidth = 0;
        int loadedHeight = 0;
        uint32_t format = 0;
        int access = 0;

        int result = SDL_QueryTexture(this->texture, &format, &access, &loadedWidth, &loadedHeight);
        if (result != 0) {
            throw SDLException("SDL_RenderCopy() failed");
        }

        this->width = static_cast<uint32_t>(loadedWidth);
        this->height = static_cast<uint32_t>(loadedHeight);
    }

    uint32_t SDLTexture::getWidth() const noexcept {
        return this->width;
    }

    uint32_t SDLTexture::getHeight() const noexcept {
        return this->height;
    }
}

