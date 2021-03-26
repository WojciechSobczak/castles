// castles.cpp : Defines the entry point for the application.
//
#include <cstring>


#include <stdio.h>
#include <string_view>
#include <chrono>
#include <thread>
#include <iostream>
#include <spdlog/spdlog.h>

#include "graphics/sdl/sdlwrap.hpp"
#include "graphics/sdl/sdl_assets_loader.hpp"
#include "graphics/sdl/sdl_game_renderer.hpp"

#include "game/game_map.hpp"
#include "game/units.hpp"
#include "graphics/game_renderer.hpp"

#include <random>


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
    spdlog::set_level(spdlog::level::debug);
    try {
        sdlwrap::SDLLifetimeGuard sdlGuard;
        sdlwrap::SDLTTFLifetimeGuard sdlTtfGuard;
        sdlwrap::SDLWindow window("Castles");
        sdlwrap::SDLRenderer renderer(window);
        renderer.enableDrawBlendMode();

        std::shared_ptr<IGameRenderer> gameRenderer = std::make_shared<SDLGameRenderer>(renderer);

        GameMap gameMap(20, 40);
        while (true) {
            SDL_Event event;
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    return 0;
                }

                if (event.type == SDL_MOUSEWHEEL) {
                    float scaleAdd = 0;
                    if (event.wheel.y > 0) {
                        scaleAdd += 0.3;
                    } else {
                        scaleAdd -= 0.3;
                    }
                    gameRenderer->addToZoomScale(scaleAdd);
                }
            }

            renderWithCap([&] {
                gameRenderer->renderGameMap(gameMap);
            });

        }
    } catch (const std::exception& e) {
        spdlog::critical("EXC: {}", e.what());
    }
    
    return 0;
}
