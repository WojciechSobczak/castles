#pragma once
#include <memory>
#include <functional>
#include "../input_handler.hpp"

class SDLInputHandler : public IInputHandler {
private:
    const uint8_t* sdlKeyboardState = nullptr;

    std::function<void(int32_t)> onMouseWheel;
    std::function<void()> onKeyPressed;
public:
    virtual bool handleInputEvents() override;

    virtual void setOnMouseWheel(std::function<void(int32_t)> onMouseWheel) override;
    virtual void setOnKeyPressed(std::function<void()> onKeyPressed) override;

    virtual bool isLeftCtrlPressed() const noexcept override;
    virtual bool isDPressed() const noexcept override;
};