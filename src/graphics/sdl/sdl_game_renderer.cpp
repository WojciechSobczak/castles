#include "sdl_game_renderer.hpp"
#include "../../game/units.hpp"
#include <spdlog/spdlog.h>

#include "layers/sdl_render_layer.hpp"

void SDLGameRenderer::addToZoomScale(float component) noexcept {
    zoomScale += component;
    if (zoomScale < 0.1) zoomScale = 0.1;
    if (zoomScale > 5) zoomScale = 5;
    spdlog::debug("Zoom scale: {}", zoomScale);
}

SDLGameRenderer::SDLGameRenderer(std::shared_ptr<sdlwrap::SDLRenderer> sdlRenderer) : sdlRenderer(sdlRenderer) {
    this->loadTextures();
}

constexpr uint8_t SDLGameRenderer::tileTypeToAssetIndex(const TileType tileType) const noexcept {
    return uint8_t(tileType);
}

void SDLGameRenderer::loadTextures() {
  
}

void SDLGameRenderer::renderLayer(IRenderLayer* renderLayer) {    
    ISDLRenderLayer* sdlRenderLayer = static_cast<ISDLRenderLayer*>(renderLayer);
    sdlRenderLayer->render(this->sdlRenderer.get());
}

IF_DEBUG_MODE_ENABLED(
    void SDLGameRenderer::setDebugMode(bool debugMode) noexcept {
        this->debugMode = debugMode;
    }
);
