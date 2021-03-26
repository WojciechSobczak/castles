#pragma once
#include <memory>
#include "../game/game_map.hpp"


class IGameRenderer {
public:
    virtual void renderGameMap(GameMap& gameMap) = 0;
    virtual void addToZoomScale(float component) noexcept = 0;
};
