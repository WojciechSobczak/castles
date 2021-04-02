#include "assets_loader.hpp"


class FSAssetsLoader : public IAssetsLoader {
private:
    std::vector<uint8_t> loadFile(const std::string& path);
public:
    virtual std::vector<uint8_t> loadTexture(const std::string& path) override;
    virtual std::vector<uint8_t> loadFont(const std::string& path) override;
};