#include "sdl_game_renderer.hpp"
#include "../../game/units.hpp"
#include <spdlog/spdlog.h>

void SDLGameRenderer::addToZoomScale(float component) noexcept {
    zoomScale += component;
    if (zoomScale < 0.1) zoomScale = 0.1;
    if (zoomScale > 5) zoomScale = 5;
    spdlog::debug("Zoom scale: {}", zoomScale);
}

SDLGameRenderer::SDLGameRenderer(sdlwrap::SDLRenderer& sdlRenderer) : sdlRenderer(sdlRenderer) {
    this->loadTextures();
}

void SDLGameRenderer::renderGameMap(GameMap& gameMap) {
    sdlRenderer.clear();
    sdlRenderer.setRenderColor({ .r = 255, .g = 255, .b = 255 });
    sdlRenderer.setRenderScale(this->zoomScale);

    constexpr uint32_t tileWidth = uint32_t(units::TILE_UNITS);
    constexpr uint32_t tileHeight = tileWidth / 2;

    int32_t rowYStart = 0;
    sdlwrap::SDLTexture* texture = nullptr;
    for (uint16_t row = 0; row < gameMap.height; row++) {
        const int32_t rowXStart = row % 2 != 0 ? tileWidth / 2 : 0;
        for (uint16_t col = 0; col < gameMap.width; col++) {
            const Tile& tile = gameMap[row][col];
            const int32_t tileRenderX = rowXStart + col * tileWidth;
            const int32_t tileHeightYOffset = tile.height;

            if (tileHeightYOffset != 0) {
                sdlRenderer.setRenderColor({ .r = 0, .g = 255, .b = 0, .a = 100 });
                sdlRenderer.drawFilledRectangle(
                    tileRenderX, 
                    rowYStart + (tileHeight / 2) - tile.height, 
                    tileWidth, 
                    (tileHeight / 2) + abs(tileHeightYOffset)
                );
            }

            sdlRenderer.drawTexture(
                *tiles[tileTypeToAssetIndex(tile.type)].get(), 
                tileRenderX, 
                rowYStart - tile.height, 
                tileWidth, 
                tileHeight
            );

            if (true) {
                std::array<SDL_Point, 5> points({
                    {
                        .x = static_cast<int>(tileRenderX),
                        .y = static_cast<int>(rowYStart + (tileHeight / 2))
                    },
                    {
                        .x = static_cast<int>(tileRenderX + (tileWidth / 2)),
                        .y = static_cast<int>(rowYStart)
                    },
                    {
                        .x = static_cast<int>(tileRenderX + tileWidth),
                        .y = static_cast<int>(rowYStart + (tileHeight / 2))
                    },
                    {
                        .x = static_cast<int>(tileRenderX + tileWidth / 2),
                        .y = static_cast<int>(rowYStart + tileHeight)
                    },
                    {
                        .x = static_cast<int>(tileRenderX),
                        .y = static_cast<int>(rowYStart + (tileHeight / 2))
                    }
                });
                sdlRenderer.setRenderColor({ .r = 255, .g = 255, .b = 255, .a = 50 });
                sdlRenderer.drawLines(points);
            }

        }
        rowYStart += tileHeight / 2;
    }

    sdlRenderer.present();
}

constexpr uint8_t SDLGameRenderer::tileTypeToAssetIndex(const TileType tileType) const noexcept {
    return uint8_t(tileType);
}

void SDLGameRenderer::loadTextures() {
    auto grassTexture = std::make_unique<sdlwrap::SDLTexture>(std::move(assetsLoader.loadTexture("tilable-IMG_0044-grey.png", sdlRenderer)));
    tiles[tileTypeToAssetIndex(TileType::GRASS)] = std::move(grassTexture);
}