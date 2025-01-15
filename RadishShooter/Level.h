#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "SpriteBatch.h"

const int constexpr TILE_WIDTH = 15;

class Level
{
public:
    explicit Level(const std::string& fileName);
    ~Level();

    void draw() const;

    [[nodiscard]] const std::vector<std::string>& getLevelData() const { return _levelData; }
    [[nodiscard]] glm::vec3 getPlayerStart() const { return  _playerStart; }

private:
    std::vector<std::string> _levelData;

    SpriteBatch _spriteBatch;

    glm::vec3 _playerStart{};
};
