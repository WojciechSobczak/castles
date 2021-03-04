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

int main(int /*argc*/, char* /*argv*/[]) {
    sdlwrap::SDLLifetimeGuard sdlGuard;
    sdlwrap::SDLTTFLifetimeGuard sdlTtfGuard;
    sdlwrap::SDLWindow window("Castles");
    sdlwrap::SDLRenderer renderer(window);
    spdlog::set_level(spdlog::level::debug);


    [&renderer]{
        SDL_Event e;

        AssetsLoader loader;
        auto texture = loader.loadTexture("tilable-IMG_0044-grey.png", renderer);
        float scale = 1;
        while (true) {
            auto beforeRenderTime = std::chrono::high_resolution_clock::now();
            renderer.clear();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    return;
                }
                if (e.type == SDL_MOUSEWHEEL ) {
                    if (e.wheel.y > 0) {
                        scale += 0.1;
                    } else {
                        scale -= 0.1;
                    }
                    spdlog::debug("Render scale: {}", scale);
                    renderer.setRenderScale(scale);
                }
            }
            {
                for (size_t i = 0; i < 50; i++) {
                    renderer.drawTexture(texture, texture.getWidth() * i, 0);
                }
                renderer.present();
            }

            auto afterRenderTime = std::chrono::high_resolution_clock::now();
            auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(afterRenderTime - beforeRenderTime);
            constexpr uint64_t fpsMax = 60;
            constexpr uint64_t frameTime = 1000 / fpsMax;
            if (deltaTime.count() < frameTime) {
                std::this_thread::sleep_for(std::chrono::milliseconds(frameTime - deltaTime.count()));
            }
        }
    }();
    return 0;
}
