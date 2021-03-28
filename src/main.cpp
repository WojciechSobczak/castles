// castles.cpp : Defines the entry point for the application.
//

#include <cstring>


#include <stdio.h>
#include <string_view>
#include <chrono>
#include <thread>
#include <iostream>
#include <random>

#include <spdlog/spdlog.h>
#include "application/sdl/sdl_application.hpp"

int main(int /*argc*/, char* /*argv*/[]) {
    spdlog::set_level(spdlog::level::debug);
    try {
        std::unique_ptr<IApplication> graphicsApp = std::make_unique<SDLApplication>();
        graphicsApp->start();
    } catch (const std::exception& e) {
        spdlog::critical("EXC: {}", e.what());
    }
    return 0;
}
