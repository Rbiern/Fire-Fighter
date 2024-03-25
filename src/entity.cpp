#include "entity.h"

Entity::Entity() {}


void Entity::move(float deltaX, float deltaY) {
    sprite.move(deltaX, deltaY);
}

sf::Sprite& Entity::getSprite() {
    return sprite;
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition();
}
void Entity::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

bool Entity::setTexture(const std::string& texturePath) {
    if (texture.loadFromFile(texturePath)) {
        sprite.setTexture(texture);
        return true;
    }
    return false;
}
