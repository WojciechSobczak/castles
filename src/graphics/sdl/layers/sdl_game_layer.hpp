#pragma once

#include "sdl_render_layer.hpp"
#include "../sdl_texture.hpp"
#include "../sdl_renderer.hpp"
#include "../../../game/game_map.hpp"

#include <memory>
#include <array>

class SDLGameLayer : public SDLRenderLayer {
private:
    std::shared_ptr<GameMap> gameMap;
    std::array<std::shared_ptr<sdlwrap::SDLTexture>, 1> tiles;

public:
    SDLGameLayer(
        std::shared_ptr<sdlwrap::SDLRenderer> renderer, 
        std::shared_ptr<GameMap> gameMap
    ) : 
        SDLRenderLayer(renderer), 
        gameMap(gameMap) 
    {};
    virtual void render() override;
    virtual void setZoomFactor(float zoomFactor) noexcept override;
    virtual void loadResources(IAssetsLoader* assetsLoader) override;
};