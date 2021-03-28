#include "application.hpp"
#include <defines.hpp>
#include <spdlog/spdlog.h>

void IApplication::start() {
    std::shared_ptr<IGameRenderer> gameRenderer = this->createRenderer();
    std::shared_ptr<IInputHandler> inputHandler = this->createInputHandler();
    inputHandler->setOnMouseWheel(
        [&](int32_t wheel) {
            float scaleAdd = 0;
            if (wheel > 0) {
                scaleAdd += 0.3;
            } else {
                scaleAdd -= 0.3;
            }
            gameRenderer->addToZoomScale(scaleAdd);
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

    while (true) {
        //If quit signal arrives
        if (inputHandler->handleInputEvents()) {
            return;
        }
        for (auto& layer : this->getRenderLayers()) {
            gameRenderer->renderLayer(layer.get());
        }
    }
}