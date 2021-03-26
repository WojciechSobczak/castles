#pragma once
#include "../game_renderer.hpp"
#include "sdlwrap.hpp"
#include "sdl_assets_loader.hpp"
#include <array>


class SDLGameRenderer : public IGameRenderer {
private:
    sdlwrap::SDLRenderer& sdlRenderer;
    SDLAssetsLoader assetsLoader;
    std::array<std::unique_ptr<sdlwrap::SDLTexture>, 1> tiles;
    float zoomScale = 1.0f;

    constexpr uint8_t tileTypeToAssetIndex(const TileType tileType) const noexcept;

public:

    bool debugMode = false;

    SDLGameRenderer(sdlwrap::SDLRenderer& sdlRenderer);

    virtual void renderGameMap(GameMap& gameMap) override;
    virtual void addToZoomScale(float component) noexcept override;
    void loadTextures();
};