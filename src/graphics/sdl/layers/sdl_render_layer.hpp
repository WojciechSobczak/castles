#pragma once
#include "../../render_layer.hpp"
#include "../sdl_renderer.hpp"
#include <chrono>

class SDLRenderLayer : public IRenderLayer {
protected:
    std::shared_ptr<sdlwrap::SDLRenderer> renderer;
public:

    virtual ~SDLRenderLayer() = default;
    SDLRenderLayer(std::shared_ptr<sdlwrap::SDLRenderer> renderer) : renderer(renderer) {};
    virtual void loadResources(IAssetsLoader* assetsLoader) = 0;
    virtual void render() = 0;
};

