#include "sdl_application.hpp"

#include "../../graphics/sdl/sdl_renderer.hpp"
#include "../../graphics/sdl/sdl_game_renderer.hpp"
#include "../../graphics/sdl/sdl_window.hpp"

#include "../../graphics/sdl/sdl_game_renderer.hpp"

#include "../../graphics/game_renderer.hpp"
#include "../../graphics/render_layer.hpp"

#include "../../game/game_map.hpp"
#include "../../game/units.hpp"

#include "../../input/input_handler.hpp"
#include "../../input/sdl/sdl_input_handler.hpp"
#include "../../graphics/sdl/layers/sdl_game_layer.hpp"

#include "../../graphics/fs_assets_loader.hpp"


SDLApplication::SDLApplication() {
    auto gameLayer = std::make_unique<SDLGameLayer>(renderer, gameMap);
    FSAssetsLoader assetsLoader;
    gameLayer->loadResources(&assetsLoader);
    this->layers.emplace_back(std::move(gameLayer));
}

std::shared_ptr<IGameRenderer> SDLApplication::createRenderer() {
    this->renderer->enableDrawBlendMode();
    return std::make_shared<SDLGameRenderer>(this->renderer);
}

std::shared_ptr<IInputHandler> SDLApplication::createInputHandler() {
    return std::make_shared<SDLInputHandler>();
}

std::vector<std::unique_ptr<IRenderLayer>>& SDLApplication::getRenderLayers() {
    return layers;
}

