#include "entity.h"

/**
 * @brief Default constructor for the Entity class.
 */
Entity::Entity() {}

/**
 * @brief Move the entity by a specified amount.
 * @param deltaX The amount to move along the x-axis.
 * @param deltaY The amount to move along the y-axis.
 */
void Entity::move(float deltaX, float deltaY) {
    sprite.move(deltaX, deltaY);
}

/**
 * @brief Get the sprite of the entity.
 * @return A reference to the entity's sprite.
 */
sf::Sprite& Entity::getSprite() {
    return sprite;
}

/**
 * @brief Get the position of the entity.
 * @return The position of the entity as a 2D vector.
 */
sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition();
}

/**
 * @brief Set the position of the entity.
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 */
void Entity::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

/**
 * @brief Set the scale of the entity.
 * @param scaleX The scale factor along the x-axis.
 * @param scaleY The scale factor along the y-axis.
 */
void Entity::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

/**
 * @brief Set the texture of the entity.
 * @param texturePath The path to the texture file.
 * @return True if the texture was successfully loaded, false otherwise.
 */
bool Entity::setTexture(const std::string& texturePath) {
    if (texture.loadFromFile(texturePath)) {
        sprite.setTexture(texture);
        return true;
    }
    return false;
}

/**
 * @brief Draw the entity on a render window.
 * @param window The render window to draw the entity on.
 */
void Entity::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}
