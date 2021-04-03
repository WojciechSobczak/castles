#include "application.hpp"
#include <spdlog/spdlog.h>

#include "graphics/fs_assets_loader.hpp"

void IApplication::start() {
    std::shared_ptr<IGameRenderer> gameRenderer = this->createRenderer();
    std::shared_ptr<IInputHandler> inputHandler = this->createInputHandler();
    inputHandler->setOnMouseWheel(
        [&](int32_t wheel) {
            static float zoomFactor = 1.f;
            zoomFactor = zoomFactor;
            if (zoomFactor < 0.1) zoomFactor = 0.1;
            if (zoomFactor > 5) zoomFactor = 5;

            if (wheel > 0) {
                zoomFactor += 0.3f;
            } else {
                zoomFactor -= 0.3f;
            }
            for (auto& layer : this->getRenderLayers()) {
                layer->setZoomFactor(zoomFactor);
            }
        }
    );
    inputHandler->setOnKeyPressed(
        [&]() {
            #ifdef DEBUG_MODE_ENABLED
            static bool debugMode = false;
            if (inputHandler->isLeftCtrlPressed() && inputHandler->isDPressed()) {
                spdlog::debug("Debug mode {}", debugMode ? "enabled" : "disabled");
                debugMode = !debugMode;
                gameRenderer->setDebugMode(debugMode);
                for (auto& layer : this->getRenderLayers()) {
                    layer->setDebugMode(debugMode);
                }
            }
            #endif // DEBUG_MODE_ENABLED
        }
    );


    auto assetsLoader = this->createAssetsLoader();
    for (auto& layer : this->getRenderLayers()) {
        layer->loadResources(assetsLoader.get());
    }
    gameRenderer->loadFPSCounterFont(assetsLoader.get());

    while (true) {
        //If quit signal arrives
        if (inputHandler->handleInputEvents()) {
            return;
        }
        gameRenderer->beforeRender();
        {
            auto beforeRenderTime = std::chrono::high_resolution_clock::now();
            for (auto& layer : this->getRenderLayers()) {
                gameRenderer->renderLayer(layer.get());
            }
            auto afterRenderTime = std::chrono::high_resolution_clock::now();
            auto renderTime = std::chrono::duration_cast<std::chrono::nanoseconds>(afterRenderTime - beforeRenderTime);
            constexpr auto second = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1));

            gameRenderer->renderFPSCounter(second.count() / renderTime.count());
        }
        gameRenderer->afterRender();
    }
}