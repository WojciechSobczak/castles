#pragma once
#include <memory>
#include <array>
#include "sdl_render_layer.hpp"
#include "../../../graphics/sdl/sdl_assets_loader.hpp"
#include "../../../graphics/sdl/sdl_texture.hpp"
#include "../../../game/game_map.hpp"

class SDLGameLayer : public ISDLRenderLayer {
private:
    std::shared_ptr<GameMap> gameMap;
    std::shared_ptr<sdlwrap::SDLRenderer> renderer;

    SDLAssetsLoader assetsLoader;
    std::array<std::unique_ptr<sdlwrap::SDLTexture>, 1> tiles;
public:
    SDLGameLayer(std::shared_ptr<GameMap> gameMap, std::shared_ptr<sdlwrap::SDLRenderer> renderer);
    virtual std::chrono::nanoseconds render(sdlwrap::SDLRenderer* renderer) override;
    virtual void loadResources() override;
    
};