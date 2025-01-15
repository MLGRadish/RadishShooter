#include "InputManager.h"

InputManager::InputManager() = default;

InputManager::~InputManager() = default;

void InputManager::onKeyPress(const unsigned int key)
{
    _keyMap[key] = true;
}

void InputManager::onKeyRelease(const unsigned int key)
{
    _keyMap[key] = false;
}

void InputManager::onMouseMove(const glm::vec2 position)
{
    mousePosition = position;
}

bool InputManager::isKeyPressed(const unsigned int key)
{
    if (auto const it = _keyMap.find(key); it != _keyMap.end()) {
        return it->second;
    } else {
        return false;
    }
}
