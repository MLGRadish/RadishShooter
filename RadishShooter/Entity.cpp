#include "Entity.h"
#include "ImageLoader.h"
#include "Level.h"

#include <ResourceManager.h>

Entity::Entity(): _speed(0.5f), _id(0), _health(100)
{
    _texture = ImageLoader::loadPNG("Resources/Textures/man.png").id;
}

Entity::~Entity() = default;

void Entity::draw(SpriteBatch &spriteBatch) const
{
    spriteBatch.add(_position, _texture, 40);
}
