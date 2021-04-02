#pragma once
#include <memory>
#include <chrono>
#include <defines.hpp>
#include "../game/game_map.hpp"
#include "render_layer.hpp"

class IGameRenderer {
#ifdef DEBUG_MODE_ENABLED
protected:
    bool debugMode = true;
public:
    virtual void setDebugMode(bool debugMode) noexcept { this->debugMode = debugMode; };
    virtual void loadFPSCounterFont(IAssetsLoader* assetsLoader) = 0;
    virtual void renderFPSCounter(size_t fps) = 0;
#endif // DEBUG_MODE_ENABLED


public:
    virtual ~IGameRenderer() = default;

    virtual void beforeRender() = 0;
    virtual void afterRender() = 0;
    virtual void renderLayer(IRenderLayer* renderLayer) = 0;


};
