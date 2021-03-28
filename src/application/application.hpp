#pragma once
#include "../graphics/game_renderer.hpp"
#include "../graphics/render_layer.hpp"
#include "../input/input_handler.hpp"
#include <vector>

class IApplication {
public:
    virtual ~IApplication() = default;
    virtual void start();

    virtual std::unique_ptr<IGameRenderer> createRenderer() = 0;
    virtual std::unique_ptr<IInputHandler> createInputHandler() = 0;
    virtual std::vector<std::unique_ptr<IRenderLayer>> createRenderLayers() = 0;
};