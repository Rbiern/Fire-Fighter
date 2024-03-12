#include "enemy.h"

Enemy::Enemy(float startX, float startY, float screenWidth)
        : screenWidth(screenWidth), movementSpeed(100.0f) { // Adjust the speed as necessary
    loadTexture("/Users/kevinlee/Desktop/cs3307asn/group19/resource/img/fire.png");
    sprite.setPosition(startX, startY);
    // Initialize other variables as needed, example:
    verticalMovementSpeed = 0.0f; // Assuming this is used for vertical movement
    startY = startY; // Store initial Y position if needed for oscillation or other logic
    time = 0.0f; // Used for time-dependent behavior, ensure it's incremented if needed
}


void Enemy::loadTexture(const std::string& path) {
    if (!texture.loadFromFile(path)) {
        // Handle loading error
    }
    sprite.setTexture(texture);
}

void Enemy::update(const sf::Time& deltaTime) {
    float moveDistance = movementSpeed * deltaTime.asSeconds();
    sprite.move(moveDistance, 0); // Move the sprite to the right

    // Check if the enemy has moved off-screen and reset its position
    if (sprite.getPosition().x > screenWidth) {
        sprite.setPosition(-sprite.getGlobalBounds().width, sprite.getPosition().y);
    }
}



void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Enemy::moveTowardsPlayer(const sf::Vector2f& playerPosition, const sf::Time& deltaTime) {
    // Calculate direction towards the player
    sf::Vector2f direction = playerPosition - sprite.getPosition();
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normalizedDirection = (distance > 0) ? direction / distance : sf::Vector2f(0, 0);

    // Update position
    sprite.move(normalizedDirection * movementSpeed * deltaTime.asSeconds());
}


