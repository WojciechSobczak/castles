#pragma once
#include <functional>
#include <atomic>

class IRenderLayer {
protected:
    #ifdef DEBUG_MODE_ENABLED
    bool debugMode = false;
    #endif // DEBUG_MODE_ENABLED
public:
    virtual ~IRenderLayer() = default;
    #ifdef DEBUG_MODE_ENABLED
    virtual void setDebugMode(bool debugMode) { this->debugMode = debugMode; };
    #endif // DEBUG_MODE_ENABLED
};