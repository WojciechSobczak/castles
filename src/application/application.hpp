#pragma once
#include "graphics/game_renderer.hpp"
#include "graphics/render_layer.hpp"
#include "graphics/assets_loader.hpp"
#include "input/input_handler.hpp"
#include <vector>

class IApplication {
public:
    virtual ~IApplication() = default;
    virtual void start();

    virtual std::shared_ptr<IGameRenderer> createRenderer() = 0;
    virtual std::shared_ptr<IInputHandler> createInputHandler() = 0;
    virtual std::shared_ptr<IAssetsLoader> createAssetsLoader() = 0;
    virtual std::vector<std::unique_ptr<IRenderLayer>>& getRenderLayers() = 0;
};