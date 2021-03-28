#include "sdl_game_layer.hpp"
#include "../../../game/units.hpp"

SDLGameLayer::SDLGameLayer(std::shared_ptr<GameMap> gameMap, std::shared_ptr<sdlwrap::SDLRenderer> renderer) : gameMap(gameMap), renderer(renderer) {
    this->loadResources();
}

std::chrono::nanoseconds SDLGameLayer::render(sdlwrap::SDLRenderer*) {
    auto beforeRenderTime = std::chrono::high_resolution_clock::now();

    renderer->clear();
    renderer->setRenderColor({ .r = 255, .g = 255, .b = 255 });
    renderer->setRenderScale(1.f);// renderer->getZoomScale());

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

    auto afterRenderTime = std::chrono::high_resolution_clock::now();
    auto frameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(afterRenderTime - beforeRenderTime);

    renderer->present();
    return frameTime;
}

void SDLGameLayer::loadResources() {
    auto grassTexture = std::make_unique<sdlwrap::SDLTexture>(std::move(assetsLoader.loadTexture("grass.png", renderer.get())));
    tiles[uint32_t(TileType::GRASS)] = std::move(grassTexture);
}
