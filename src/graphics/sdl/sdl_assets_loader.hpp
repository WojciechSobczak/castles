#pragma once
#include "sdl_surface.hpp"
#include "sdl_texture.hpp"
#include "sdl_renderer.hpp"

class SDLAssetsLoader {

public:
    sdlwrap::SDLSurface loadImage(const std::string& path);
    sdlwrap::SDLTexture loadTexture(const std::string& path, sdlwrap::SDLRenderer* renderer);

};