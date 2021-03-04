#pragma once
#include "sdlwrap/sdlwrap.hpp"

class AssetsLoader {

public:
    sdlwrap::SDLSurface loadImage(const std::string& path);
    sdlwrap::SDLTexture loadTexture(const std::string& path, sdlwrap::SDLRenderer& renderer);

};