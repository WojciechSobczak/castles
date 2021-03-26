#pragma once
#include "sdlwrap.hpp"

class SDLAssetsLoader {

public:
    sdlwrap::SDLSurface loadImage(const std::string& path);
    sdlwrap::SDLTexture loadTexture(const std::string& path, sdlwrap::SDLRenderer& renderer);

};