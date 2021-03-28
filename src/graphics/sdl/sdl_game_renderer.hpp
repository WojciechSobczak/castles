#pragma once
#include "../game_renderer.hpp"
#include "sdl_assets_loader.hpp"
#include <array>


class SDLGameRenderer : public IGameRenderer {
private:
    std::shared_ptr<sdlwrap::SDLRenderer> sdlRenderer;
    float zoomScale = 1.0f;

    constexpr uint8_t tileTypeToAssetIndex(const TileType tileType) const noexcept;
    bool debugMode = true;

public:

    SDLGameRenderer(std::shared_ptr<sdlwrap::SDLRenderer> sdlRenderer);
    virtual ~SDLGameRenderer() = default;

    virtual void addToZoomScale(float component) noexcept override;
    virtual void renderLayer(IRenderLayer* renderLayer) override;

    IF_DEBUG_MODE_ENABLED(virtual void setDebugMode(bool debugMode) noexcept override);

    void loadTextures();
};