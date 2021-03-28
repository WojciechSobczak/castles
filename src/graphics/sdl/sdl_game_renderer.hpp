#pragma once
#include "../game_renderer.hpp"
#include "sdl_assets_loader.hpp"
#include "sdl_render_layer.hpp"
#include <array>


class SDLGameRenderer : public IGameRenderer {
private:
    sdlwrap::SDLRenderer& sdlRenderer;
    SDLAssetsLoader assetsLoader;
    std::array<std::unique_ptr<sdlwrap::SDLTexture>, 1> tiles;
    float zoomScale = 1.0f;

    constexpr uint8_t tileTypeToAssetIndex(const TileType tileType) const noexcept;
    bool debugMode = true;

public:

    SDLGameRenderer(sdlwrap::SDLRenderer& sdlRenderer);
    virtual ~SDLGameRenderer() = default;

    virtual void addToZoomScale(float component) noexcept override;
    virtual std::chrono::nanoseconds renderLayer(IRenderLayer& irenderLayer) override;

    IF_DEBUG_MODE_ENABLED(virtual void setDebugMode(bool debugMode) noexcept override);

    void loadTextures();
};