#pragma once

#include <memory>

#include "../application.hpp"
#include "../../graphics/sdl/sdl_window.hpp"
#include "sdl_small_guards.hpp"
#include "../../graphics/sdl/sdl_renderer.hpp"


class SDLApplication : public IApplication {
private:
    sdlwrap::SDLLifetimeGuard sdlGuard{};
    sdlwrap::SDLTTFLifetimeGuard sdlTtfGuard{};
    sdlwrap::SDLWindow window{ "Castles" };
    std::shared_ptr<sdlwrap::SDLRenderer> renderer = std::make_unique<sdlwrap::SDLRenderer>(window);


    std::shared_ptr<GameMap> gameMap = std::make_unique<GameMap>(50, 100);
    std::vector<std::unique_ptr<IRenderLayer>> layers{};
public:
    SDLApplication();

    virtual std::shared_ptr<IGameRenderer> createRenderer() override;
    virtual std::shared_ptr<IInputHandler> createInputHandler() override;
    virtual std::vector<std::unique_ptr<IRenderLayer>>& getRenderLayers() override;
};