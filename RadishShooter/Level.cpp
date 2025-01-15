#include "Level.h"

#include <ResourceManager.h>
#include <fstream>
#include <iostream>
#include <err.h>

Level::Level(const std::string & fileName)
{
    std::ifstream file;
    file.open(fileName);

    if (file.fail()) {
        fatalError("Failed to load level: " + fileName);
    }

    std::string tmp;

    while (std::getline(file, tmp)) {
        _levelData.push_back(tmp);
    }

    _spriteBatch.init();

    for (auto y = 0; y < _levelData.size(); y++)
    {
        for (auto x = 0; x < _levelData[y].size(); x++)
        {
            char tile = _levelData[y][x];

            glm::vec3 destRect(x * TILE_WIDTH, 0, y * TILE_WIDTH);

            switch (tile)
            {
                case 'B':
                    _spriteBatch.add(destRect, ResourceManager::getTexture("Resources/Textures/brick.png").id, TILE_WIDTH);
                    break;
                case 'G':
                    _spriteBatch.add(destRect, ResourceManager::getTexture("Resources/Textures/grass_04.png").id, TILE_WIDTH);
                    break;
                case '&':
                    _spriteBatch.add(destRect, ResourceManager::getTexture("Resources/Textures/grass_04.png").id, TILE_WIDTH);
                    _playerStart.x = static_cast<float>(x) * TILE_WIDTH;
                    _playerStart.y = 0.1f;
                    _playerStart.z = static_cast<float>(y) * TILE_WIDTH;
                    break;
                default:
                    break;
            }
        }
    }
    _spriteBatch.createBatch();
}

Level::~Level() = default;

void Level::draw() const
{
    _spriteBatch.renderBatch();
}
