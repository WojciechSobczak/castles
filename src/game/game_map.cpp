#include "game_map.hpp"

GameMap::GameMap(uint32_t width, uint32_t height) : width(width), height(height), tiles(height) {
    for (auto& tile : this->tiles) {
        tile.resize(width);
    }
}

void GameMap::generateTiles() {
    
}

void GameMap::clearTiles() {
}

std::vector<Tile>& GameMap::operator[](uint32_t row) {
    return this->tiles[row];
}

std::vector<Tile>& GameMap::at(uint32_t row) {
    return this->tiles[row];
}

Tile& GameMap::at(uint32_t row, uint32_t col) {
    return this->tiles[row][col];
}
