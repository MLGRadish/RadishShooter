#pragma once
#include "Entity.h"

#include <vector>
#include "NetworkManager.h"

class netPlayerManager
{
public:
    netPlayerManager();
    ~netPlayerManager();

    void init(std::vector<Entity*>* entityList);

    static void update(NetworkManager& networkManager);

private:
    std::vector<Entity*>* _netPlayers{};
};
