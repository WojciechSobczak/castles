#include "sdl_game_layer.hpp"
#include "../../../game/units.hpp"
#include <spdlog/spdlog.h>

void SDLGameLayer::render() {
    renderer->setRenderColor({ .r = 255, .g = 255, .b = 255 });
    renderer->setRenderScale(this->zoomFactor);

    constexpr uint32_t tileWidth = uint32_t(units::TILE_UNITS);
    constexpr uint32_t tileHeight = tileWidth / 2;

    int32_t rowYStart = 0;
    sdlwrap::SDLTexture* texture = nullptr;
    for (uint16_t row = 0; row < this->gameMap->height; row++) {
        const int32_t rowXStart = row % 2 != 0 ? tileWidth / 2 : 0;
        for (uint16_t col = 0; col < this->gameMap->width; col++) {
            const Tile& tile = gameMap->at(row, col);
            const int32_t tileRenderX = rowXStart + col * tileWidth;
            const int32_t tileHeightYOffset = tile.height;

            if (tileHeightYOffset != 0) {
                renderer->setRenderColor({ .r = 0, .g = 255, .b = 0, .a = 100 });
                renderer->drawFilledRectangle(
                    tileRenderX, 
                    rowYStart + (tileHeight / 2) - tile.height, 
                    tileWidth, 
                    (tileHeight / 2) + abs(tileHeightYOffset)
                );
            }

            renderer->drawTexture(
                tiles[int32_t(tile.type)].get(),
                tileRenderX, 
                rowYStart - tile.height, 
                tileWidth, 
                tileHeight
            );

            #ifdef DEBUG_MODE_ENABLED
            if (this->debugMode) {
                const std::array<const SDL_Point, 5> points({
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
                renderer->setRenderColor({ .r = 255, .g = 255, .b = 255, .a = 50 });
                renderer->drawLines(points);
            }
            #endif // DEBUG_MODE_ENABLED

        }
        rowYStart += tileHeight / 2;
    }
}

void SDLGameLayer::loadResources(IAssetsLoader* assetsLoader) {
    auto bytes = assetsLoader->loadTexture("grass.png");
    sdlwrap::SDLRWops rwops = SDL_RWFromMem(bytes.data(), bytes.size());
    if (rwops.get() == nullptr) {
        throw sdlwrap::SDLException("SDL_RWFromMem() failed");
    }
    sdlwrap::SDLSurface surface = IMG_Load_RW(rwops.get(), 0);
    tiles[uint32_t(TileType::GRASS)] = std::make_shared<sdlwrap::SDLTexture>(renderer->createTexture(surface));
}

void SDLGameLayer::setZoomFactor(float zoomFactor) noexcept {
    this->zoomFactor = zoomFactor;
    if (this->zoomFactor < 0.1) this->zoomFactor = 0.1;
    if (this->zoomFactor > 5) this->zoomFactor = 5;
    spdlog::debug("Game layer zoom scale: {}", this->zoomFactor);
}
