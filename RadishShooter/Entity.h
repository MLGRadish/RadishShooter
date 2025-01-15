#pragma once
#include "SpriteBatch.h"
#include <glm/glm.hpp>

class Entity
{
public:
    Entity();
    virtual ~Entity();

    void draw(SpriteBatch &spriteBatch) const;

    [[nodiscard]] glm::vec3 getPosition() const { return _position; }
    [[nodiscard]] int getId() const { return _id; }
    [[nodiscard]] int getHealth() const { return _health; }

    void updatePosition(const glm::vec3 position) { _position = position; };
    void updateId(const int id) { _id = id; };

protected:
    GLuint _texture;
    glm::vec3 _position{};
    float _speed;
    int _id;
    int _health;
};
