#include "sdl_game_renderer.hpp"
#include "../../game/units.hpp"
#include <spdlog/spdlog.h>

#include "layers/sdl_render_layer.hpp"

void SDLGameRenderer::renderLayer(IRenderLayer* renderLayer) {    
    SDLRenderLayer* sdlRenderLayer = static_cast<SDLRenderLayer*>(renderLayer);
    sdlRenderLayer->render();
}

void SDLGameRenderer::beforeRender() {
    this->renderer->clear();
}

void SDLGameRenderer::afterRender() {
    this->renderer->present();
}


#ifdef DEBUG_MODE_ENABLED
void SDLGameRenderer::renderFPSCounter(size_t fps) {    
    std::string message = "FPS: " + std::to_string(fps);
    auto texture = this->renderer->createTextTexture(this->fpsFont.get(), message, { .r = 255, .g = 255, .b = 255, .a = 0 });
    this->renderer->setRenderScale(1.f);
    this->renderer->drawTexture(&texture, 0, 0);
};

void SDLGameRenderer::loadFPSCounterFont(IAssetsLoader* assetsLoader) {
    static auto bytes = assetsLoader->loadFont("courier_prime.ttf");
    static sdlwrap::SDLRWops rwops = SDL_RWFromMem(bytes.data(), bytes.size());
    if (rwops.get() == nullptr) {
        throw sdlwrap::SDLException("SDL_RWFromMem() failed");
    }
    sdlwrap::SDLTTFFont font = TTF_OpenFontRW(rwops.get(), 0, 16);
    if (font.get() == nullptr) {
        throw sdlwrap::SDLException("TTF_OpenFontRW() failed");
    }
    this->fpsFont = std::make_shared<sdlwrap::SDLTTFFont>(std::move(font));
}
#endif // DEBUG_MODE_ENABLED

