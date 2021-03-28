#pragma once
#include "../../render_layer.hpp"
#include "../sdl_renderer.hpp"
#include <chrono>

class ISDLRenderLayer : public IRenderLayer {
public:
    virtual ~ISDLRenderLayer() = default;
    virtual std::chrono::nanoseconds render(sdlwrap::SDLRenderer* renderer) = 0;
    virtual void loadResources() = 0;
};

