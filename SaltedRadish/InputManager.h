#pragma once
#include <glm/glm.hpp>
#include <unordered_map>

class InputManager {
public:
    InputManager();
    ~InputManager();

    void onKeyPress(unsigned int key);
    void onKeyRelease(unsigned int key);
    void onMouseMove(glm::vec2 position);

    bool isKeyPressed(unsigned int key);

    glm::vec2 mousePosition{};

private:
    std::unordered_map<unsigned int, bool> _keyMap;
};
