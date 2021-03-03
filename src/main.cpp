// castles.cpp : Defines the entry point for the application.
//
#include <cstring>

#include "sdlwrap/sdlwrap.hpp"
#include <stdio.h>
#include <string_view>
#include <chrono>
#include <thread>

#include "assets_loader.hpp"

int main(int /*argc*/, char* /*argv*/[]) {
    sdlwrap::SDLLifetimeGuard sdlGuard;
    sdlwrap::SDLTTFLifetimeGuard sdlTtfGuard;
    sdlwrap::SDLWindow window("Castles");
    sdlwrap::SDLRenderer renderer(window);


    [&renderer]{
        SDL_Event e;

        AssetsLoader loader;
        auto surface = loader.loadImage("tilable-IMG_0044-grey.png");
        auto texture = renderer.createTexture(surface);
        while (true) {
            auto beforeRenderTime = std::chrono::high_resolution_clock::now();
            renderer.clear();
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    return;
                }
            }
            {
                renderer.drawTexture(texture, 0, 0);
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
