#include "sdl_pc_application.hpp"

#include "graphics/sdl/sdl_game_renderer.hpp"
#include "graphics/sdl/sdl_renderer.hpp"
#include "graphics/sdl/layers/sdl_game_layer.hpp"
#include "graphics/fs_assets_loader.hpp"

#include "input/sdl/sdl_input_handler.hpp"

#include "game/game_map.hpp"



SDLPCApplication::SDLPCApplication() {
    this->layers.emplace_back(std::make_unique<SDLGameLayer>(renderer, gameMap));
}

std::shared_ptr<IGameRenderer> SDLPCApplication::createRenderer() {
    this->renderer->enableDrawBlendMode();
    return std::make_shared<SDLGameRenderer>(this->renderer);
}

std::shared_ptr<IInputHandler> SDLPCApplication::createInputHandler() {
    return std::make_shared<SDLInputHandler>();
}

std::shared_ptr<IAssetsLoader> SDLPCApplication::createAssetsLoader() {
    return std::make_shared<FSAssetsLoader>();
}

std::vector<std::unique_ptr<IRenderLayer>>& SDLPCApplication::getRenderLayers() {
    return layers;
}



