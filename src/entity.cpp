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
void Entity::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}
bool Entity::setTexture(const std::string& texturePath) {
    if (texture.loadFromFile(texturePath)) {
        sprite.setTexture(texture);
        return true;
    }
    return false;
}
void Entity::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}
