#include "entity.h"

Entity::Entity() {}

void Entity::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Entity::move(float deltaX, float deltaY) {
    sprite.move(deltaX, deltaY);
}

sf::Sprite& Entity::getSprite() {
    return sprite;
}

bool Entity::setTexture(const std::string& texturePath) {
    if (texture.loadFromFile(texturePath)) {
        sprite.setTexture(texture);
        return true;
    }
    return false;
}
