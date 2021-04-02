#pragma once
#include <functional>
#include <atomic>
#include "assets_loader.hpp"

class IRenderLayer {
#ifdef DEBUG_MODE_ENABLED
protected:
    bool debugMode = false;
public:
    virtual void setDebugMode(bool debugMode) { this->debugMode = debugMode; };
    virtual bool isDebugMode() { return this->debugMode; };
#endif // DEBUG_MODE_ENABLED   

protected:
    float zoomFactor = 1.0f;
public:

    virtual ~IRenderLayer() = default;

    virtual void setZoomFactor(float zoomFactor) noexcept { this->zoomFactor = zoomFactor; };
    virtual float getZoomFactor() noexcept { return this->zoomFactor; };

    virtual void loadResources(IAssetsLoader* assetsLoader) = 0;
};