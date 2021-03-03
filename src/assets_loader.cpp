#include "assets_loader.hpp"
#include <filesystem>

sdlwrap::SDLSurface AssetsLoader::loadImage(const std::string& imagePath) {
    #ifdef ASSETS_PREFIX
    auto path = std::string(ASSETS_PREFIX) + imagePath;
    #else
    auto& path = imagePath;
    #endif

    if (!std::filesystem::exists(path)) {
        throw std::exception("File does not exists");
    }

    sdlwrap::SDLSurface surface = IMG_Load(path.c_str());
    if (surface.get() == nullptr) {
        throw sdlwrap::SDLException("IMG_Load() failed");
    }
    return surface;
}