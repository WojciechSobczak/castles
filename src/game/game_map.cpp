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
