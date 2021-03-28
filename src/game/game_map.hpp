#pragma once
#include <inttypes.h>
#include <vector>

#include "tile.hpp"

class GameMap {
private:
    std::vector<std::vector<Tile>> tiles;
public:
    const uint32_t width{};
    const uint32_t height{};

    GameMap(uint32_t width, uint32_t height);

    void generateTiles();
    void clearTiles();

    std::vector<Tile>& operator[](uint32_t row);
    std::vector<Tile>& at(uint32_t row);
    Tile& at(uint32_t row, uint32_t col);

};