#pragma once

enum class TileType {
    GRASS, SAND, BUILDING
};

class Tile {
public:
    const bool accessible{true};
    int8_t height{0};
    TileType type = TileType::GRASS;

    Tile() = default;
};