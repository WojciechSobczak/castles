#include "sdl_application.hpp"

#include "../../graphics/sdl/sdl_renderer.hpp"
#include "../../graphics/sdl/sdl_assets_loader.hpp"
#include "../../graphics/sdl/sdl_game_renderer.hpp"
#include "../../graphics/sdl/sdl_window.hpp"

#include "../../graphics/sdl/sdl_render_layer.hpp"
#include "../../graphics/sdl/sdl_game_renderer.hpp"

#include "../../graphics/game_renderer.hpp"
#include "../../graphics/render_layer.hpp"

#include "../../game/game_map.hpp"
#include "../../game/units.hpp"

#include "../../input/input_handler.hpp"
#include "../../input/sdl/sdl_input_handler.hpp"


SDLApplication::SDLApplication() { }

std::unique_ptr<IGameRenderer> SDLApplication::createRenderer() {
    this->renderer.enableDrawBlendMode();
    return std::make_unique<SDLGameRenderer>(this->renderer);
}

std::unique_ptr<IInputHandler> SDLApplication::createInputHandler() {
    return std::make_unique<SDLInputHandler>();
}

std::vector<std::unique_ptr<IRenderLayer>> SDLApplication::createRenderLayers() {
    return std::vector<std::unique_ptr<IRenderLayer>>();
}

