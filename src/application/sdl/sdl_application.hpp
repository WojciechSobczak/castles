#pragma once

#include <memory>

#include "../application.hpp"
#include "../../graphics/sdl/sdl_window.hpp"
#include "../../sdl/sdl_small_guards.hpp"
#include "../../graphics/sdl/sdl_renderer.hpp"


class SDLApplication : public IApplication {
private:
    sdlwrap::SDLLifetimeGuard sdlGuard{};
    sdlwrap::SDLTTFLifetimeGuard sdlTtfGuard{};
    sdlwrap::SDLWindow window{ "Castles" };
    sdlwrap::SDLRenderer renderer{ window };
public:
    SDLApplication();

    virtual std::unique_ptr<IGameRenderer> createRenderer() override;
    virtual std::unique_ptr<IInputHandler> createInputHandler() override;
    virtual std::vector<std::unique_ptr<IRenderLayer>> createRenderLayers() override;
};