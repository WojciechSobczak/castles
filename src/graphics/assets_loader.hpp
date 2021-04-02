#pragma once
#include <inttypes.h>
#include <vector>
#include <string>

class IAssetsLoader {
public:
    virtual std::vector<uint8_t> loadTexture(const std::string& path) = 0;
    virtual std::vector<uint8_t> loadFont(const std::string& path) = 0;
};

