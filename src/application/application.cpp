#include "application.hpp"
#include <defines.hpp>

void IApplication::start() {
    std::unique_ptr<IGameRenderer> gameRenderer = this->createRenderer();
    std::unique_ptr<IInputHandler> inputHandler = this->createInputHandler();
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
                debugMode = !debugMode;
                gameRenderer->setDebugMode(debugMode);
            }
            #endif // DEBUG_MODE_ENABLED
        }
    );

    //std::unique_ptr<IRenderLayer> gameLayer = this->createRenderer();

    GameMap gameMap(50, 100);
    while (true) {
        //If quit signal arrives
        if (inputHandler->handleInputEvents()) {
            return;
        }
        //gameRenderer->renderLayer(*gameLayer.get());
    }
}