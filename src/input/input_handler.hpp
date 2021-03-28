#pragma once
#include <functional>

class IInputHandler {
public:
    virtual ~IInputHandler() = default;
    virtual bool handleInputEvents() = 0;

    virtual void setOnMouseWheel(std::function<void(int32_t)> onMouseWheel) = 0;
    virtual void setOnKeyPressed(std::function<void()> onKeyPressed) = 0;

    virtual bool isLeftCtrlPressed() const noexcept = 0;
    virtual bool isDPressed() const noexcept = 0;

};