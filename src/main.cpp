// castles.cpp : Defines the entry point for the application.
//
#include <cstring>

#include "sdlwrap/sdlwrap.hpp"
#include <stdio.h>
#include <string_view>
#include <chrono>
#include <thread>

#include <spdlog/spdlog.h>

#include "assets_loader.hpp"

#include "game/game_map.hpp"
#include "game/units.hpp"

#include <random>

void calculatePerspectiveFactors(SDL_Event& event, float& zoomScale/*, float& cameraAngleFactor*/) {
    if (event.type == SDL_MOUSEWHEEL) {
        const uint8_t* keysState = SDL_GetKeyboardState(NULL);
        float scaleAdd = 0;
        if (event.wheel.y > 0) {
            scaleAdd += 0.3;
        } else {
            scaleAdd -= 0.3;
        }

        if (keysState[SDL_SCANCODE_LCTRL] == 1) {
        /*    cameraAngleFactor += scaleAdd;
            if (cameraAngleFactor < 0.1) cameraAngleFactor = 0.1;
            if (cameraAngleFactor > 1) cameraAngleFactor = 1;*/
        } else {
            zoomScale += scaleAdd;
            if (zoomScale < 0.1) zoomScale = 0.1;
            if (zoomScale > 5) zoomScale = 5;
        }
        //spdlog::debug("Zoom scale: {} | Camera angle: {}", zoomScale, cameraAngleFactor);
        spdlog::debug("Zoom scale: {}", zoomScale);
    }
}

void renderWithCap(std::function<void()> func, uint16_t maxFrames = 60) {
    auto beforeRenderTime = std::chrono::high_resolution_clock::now();
    {
        func();
    }
    auto afterRenderTime = std::chrono::high_resolution_clock::now();
    auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(afterRenderTime - beforeRenderTime);
    constexpr uint64_t fpsMax = 10;
    constexpr uint64_t frameTime = 1000 / fpsMax;
    if (deltaTime.count() < frameTime) {
        std::this_thread::sleep_for(std::chrono::milliseconds(frameTime - deltaTime.count()));
    }

    //spdlog::debug("Frame time: {}ms", deltaTime.count());
}

int main(int /*argc*/, char* /*argv*/[]) {
    sdlwrap::SDLLifetimeGuard sdlGuard;
    sdlwrap::SDLTTFLifetimeGuard sdlTtfGuard;
    sdlwrap::SDLWindow window("Castles");
    sdlwrap::SDLRenderer renderer(window);
    renderer.enableDrawBlendMode();
    spdlog::set_level(spdlog::level::debug);


    [&renderer]{
        constexpr float cameraAngleFactor = 0.5;

        AssetsLoader loader;
        auto grassTexture = loader.loadTexture("tilable-IMG_0044-grey.png", renderer);

        std::random_device randomDevice;
        std::default_random_engine engine(randomDevice());
        std::uniform_int_distribution<uint16_t> uniformDist(0, 10);

        GameMap gameMap(20, 40);
        for (uint16_t row = 0; row < gameMap.height; row++) {
            int8_t height = 0;
            int8_t incNum = 1;
            for (uint16_t col = 0; col < gameMap.width; col++) {
                if (height > 10) {
                    incNum = -incNum;
                }
                gameMap[row][col].height = height += incNum;
            }
            break;
        }

        float zoomScale = 1;
        while (true) {
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) return;
                calculatePerspectiveFactors(e, zoomScale);
            }
            renderWithCap([&] {
                renderer.clear();
                renderer.setRenderColor({ .r = 255, .g = 255, .b = 255 });
                renderer.setRenderScale(zoomScale);

                const uint32_t tileWidth = uint32_t(50);
                const uint32_t tileHeight = tileWidth / 2;
                
                int32_t rowYStart = 0;
                sdlwrap::SDLTexture* texture = nullptr;
                for (uint16_t row = 0; row < gameMap.height; row++) {
                    const int32_t rowXStart = row % 2 != 0 ? tileWidth / 2 : 0;
                    for (uint16_t col = 0; col < gameMap.width; col++) {
                        Tile& tile = gameMap[row][col];
                        switch (tile.type) 	{
                            case TileType::GRASS: {
                                texture = &grassTexture;
                                break;
                            }
                        }
                        int32_t tileRenderX = rowXStart + col * tileWidth;
                        int32_t tileHeightYOffset = tile.height;
                        if (tileHeightYOffset != 0) {
                            renderer.setRenderColor({ .r = 0, .g = 255, .b = 0, .a = 100 });
                            renderer.drawFilledRectangle(tileRenderX, rowYStart + (tileHeight / 2) - tile.height, tileWidth, (tileHeight / 2) + abs(tileHeightYOffset));
                        }
                        
                        if (texture != nullptr) [[likely]] {
                            renderer.drawTexture(*texture, tileRenderX, rowYStart - tile.height, tileWidth, tileHeight);
                        }
                    }
                    rowYStart += tileHeight / 2;
                }
                
                renderer.present();
            });
        }
    }();
    return 0;
}
