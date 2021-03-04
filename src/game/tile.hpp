#pragma once


class Tile {
public:
    const bool accessible{true};
    float height{0};

    Tile() = default;
    Tile(bool accessible, float height) : accessible(accessible), height(height) {};
};