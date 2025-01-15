#include "Player.h"
#include "Entity.h"
#include "Level.h"

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL.h>
#include <cstdio>
//#include <message.pb.h>
#include <string>

Player::Player() = default;

Player::~Player() = default;

void Player::init(const float speed, const Level* levelData)
{
    _speed = speed;
    _position = levelData->getPlayerStart();
    _levelData = levelData->getLevelData();
}

void Player::updateCollision()
{
    const int y1 = static_cast<int>(_position.z) / 15;
    const int x1 = static_cast<int>(_position.x) / 15;

    const int y2 = static_cast<int>(_position.z + 15) / 15;
    const int x2 = static_cast<int>(_position.x + 15) / 15;

    // top
    if (_levelData[y1][x1] == 'B') {
        // right
        if (_levelData[y1][x2] == 'B') {
            _position.z += std::abs(_position.z - static_cast<float>(y1 * 15 + 15));
        }
        // left
        if (_levelData[y2][x1] == 'B') {
            _position.x += std::abs(_position.x - static_cast<float>(x1 * 15 + 15));
        }
    }

    // bottom
    if (_levelData[y2][x2] == 'B') {
        // right
        if (_levelData[y1][x2] == 'B') {
            _position.x -= std::abs(_position.x - static_cast<float>(x2 * 15 - 15));
        }
        // left
        if (_levelData[y2][x1] == 'B') {
            _position.z -= std::abs(_position.z - static_cast<float>(y2 * 15 - 15));
        }
    }
}

void Player::netUpdate(NetworkManager& networkManager)
{
    /*message::Message msg;
    msg.set_corpus(message::Corpus::UPDATE);

    auto *pos = new message::vec3;
    pos->set_x(getPosition().x);
    pos->set_y(getPosition().y);
    pos->set_z(getPosition().z);

    msg.set_allocated_pos(pos);

    size_t size = msg.ByteSizeLong();
    void *buffer = malloc(size);
    msg.SerializeToArray(buffer, size);

    networkManager.send(buffer, size, false);
    free(buffer);*/
}

void Player::update(InputManager& inputManager, NetworkManager& networkManager)
{
    if (inputManager.isKeyPressed(SDLK_w)) {
        _position.z -= _speed;
        _position.x -= _speed;
    }

    if (inputManager.isKeyPressed(SDLK_s)) {
        _position.z += _speed;
        _position.x += _speed;
    }

    if (inputManager.isKeyPressed(SDLK_d)) {
        _position.z -= _speed;
        _position.x += _speed;
    }

    if (inputManager.isKeyPressed(SDLK_a)) {
        _position.z += _speed;
        _position.x -= _speed;
    }

    updateCollision();

    netUpdate(networkManager);
}
