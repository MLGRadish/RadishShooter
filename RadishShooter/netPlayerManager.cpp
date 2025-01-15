#include "netPlayerManager.h"

netPlayerManager::netPlayerManager() = default;

netPlayerManager::~netPlayerManager() = default;

void netPlayerManager::init(std::vector<Entity*>* entityList) {
    _netPlayers = entityList;
}

void netPlayerManager::update(NetworkManager& networkManager) {

}
