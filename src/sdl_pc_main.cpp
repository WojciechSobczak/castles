#include <spdlog/spdlog.h>
#include "application/sdl/sdl_pc_application.hpp"
#include "application/sdl/sdl_small_guards.hpp"

int main(int /*argc*/, char* /*argv*/[]) {
    spdlog::set_level(spdlog::level::debug);
    try {
        std::unique_ptr<IApplication> graphicsApp = std::make_unique<SDLPCApplication>();
        graphicsApp->start();
    } catch (const sdlwrap::SDLException& e) {
        spdlog::critical("SDL Error: {}", e.getMessage());
    } catch (const std::exception& e) {
        spdlog::critical("Error: {}", e.what());
    }
    return 0;
}
