#pragma once

#include <InputManager.h>
#include "NetworkManager.h"
#include <cmath>
#include <glm/glm.hpp>

#include "Entity.h"
#include "Level.h"

class Player : public Entity
{
public:
    Player();
    ~Player() override;

    void init(float speed, const Level* levelData);

    void update(InputManager& inputManager, NetworkManager& networkManager);

    static void netUpdate(NetworkManager& networkManager);

    void updateCollision();

    static int getHeading(const InputManager& inputManager) {
        // center of screen
        constexpr double x1 = static_cast<double>(1024)/2;
        constexpr double y1 = static_cast<double>(768)/2;

        // mouse position
        const double x2 = inputManager.mousePosition.x;
        const double y2 = inputManager.mousePosition.y;

        // math magic
        return static_cast<int>(std::atan2(x2 - x1, y1 - y2) * (180.0 / M_PI) + 360) % 360;
    }

private:
    std::vector<std::string> _levelData;
};
