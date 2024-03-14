#include "enemy.h"

// Constructor
Enemy::Enemy(float startX, float startY, float screenWidth)
        : Entity(), screenWidth(screenWidth), movementSpeed(5.0f) { // Call Entity's constructor
    setTexture("../../resource/img/fire.png"); // Set the texture
    setPosition(startX, startY); // Set the initial position
    verticalMovementSpeed = 0.0f;
    this->startY = startY;
    time = 0.0f;
}

sf::Vector2u Enemy::getSize() const {
    return texture.getSize();
}

void Enemy::update(const sf::Time& deltaTime) {
    float moveDistance = movementSpeed * deltaTime.asSeconds();
    move(moveDistance, 0); // Move horizontally

    // If the enemy moves off-screen, reset its position
    if (getSprite().getPosition().x > screenWidth) {
        setPosition(-getSprite().getGlobalBounds().width, getSprite().getPosition().y);
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(getSprite()); // Draw the sprite managed by Entity
}

void Enemy::moveTowardsPlayer(const sf::Vector2f& playerPosition, const sf::Time& deltaTime) {
    sf::Vector2f direction = playerPosition - getSprite().getPosition();
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normalizedDirection = (distance > 0) ? direction / distance : sf::Vector2f(0, 0);

    move(normalizedDirection.x * movementSpeed * deltaTime.asSeconds(), normalizedDirection.y * movementSpeed * deltaTime.asSeconds());
}

void Enemy::loadTexture(const std::string& path) {
    if (!texture.loadFromFile(path)) {
        // Handle loading error
    }
    sprite.setTexture(texture);
}
