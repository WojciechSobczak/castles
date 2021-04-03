#pragma once
#include "sdl_renderer.hpp"
#include "../game_renderer.hpp"
#include <array>


class SDLGameRenderer : public IGameRenderer {
#ifdef DEBUG_MODE_ENABLED
protected:
    std::shared_ptr<sdlwrap::SDLTTFFont> fpsFont{};
    virtual void renderFPSCounter(size_t fps) override;
    virtual void loadFPSCounterFont(IAssetsLoader* assetsLoader) override;
#endif // DEBUG_MODE_ENABLED
private:
    std::shared_ptr<sdlwrap::SDLRenderer> renderer;
public:

    SDLGameRenderer(std::shared_ptr<sdlwrap::SDLRenderer> renderer) : renderer(renderer) {};
    virtual ~SDLGameRenderer() = default;

    virtual void renderLayer(IRenderLayer* renderLayer) override;
    virtual void beforeRender() override;
    virtual void afterRender() override;

};