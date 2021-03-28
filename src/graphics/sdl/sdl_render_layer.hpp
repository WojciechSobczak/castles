#pragma once
#include "../render_layer.hpp"
#include "sdl_renderer.hpp"

class SDLRenderLayer : public IRenderLayer {
public:
    void render(sdlwrap::SDLRenderer& renderer);
};