#include "fs_assets_loader.hpp"

#include <fstream>
#include <iterator>
#include <filesystem>
#include <spdlog/spdlog.h>

#ifdef ASSETS_PREFIX
constexpr std::string_view BASE_PATH = ASSETS_PREFIX;
#else
constexpr std::string_view BASE_PATH = "./assets/";
#endif

std::vector<uint8_t> FSAssetsLoader::loadFile(const std::string& path) {
    const std::filesystem::path filePath(path);
    if (!std::filesystem::exists(filePath)) {
        throw std::runtime_error("Filepath: " + path + " does not exists");
    }
    std::ifstream fileStream(path, std::ios_base::binary);
    return { std::istreambuf_iterator<char>(fileStream), {} };
}

std::vector<uint8_t> FSAssetsLoader::loadTexture(const std::string& path) {
    const std::string texturePath = std::string(BASE_PATH) + "/textures/" + path;
    spdlog::debug("Loading texture from: {}", path);
    return loadFile(texturePath);
}

std::vector<uint8_t> FSAssetsLoader::loadFont(const std::string& path) {
    const std::string fontPath = std::string(BASE_PATH) + "/fonts/" + path;
    spdlog::debug("Loading font from: {}", path);
    return loadFile(fontPath);
}
