#pragma once
#include <memory>
#include <chrono>
#include <defines.hpp>
#include "../game/game_map.hpp"
#include "render_layer.hpp"

class IGameRenderer {
public:
    virtual ~IGameRenderer() = default;

    virtual std::chrono::nanoseconds renderLayer(IRenderLayer& renderLayer) = 0;
    virtual void addToZoomScale(float component) noexcept = 0;

    IF_DEBUG_MODE_ENABLED(virtual void setDebugMode(bool debugMode) noexcept = 0);
};
