/**
 * @file enemy.cpp
 * Implementation of the Enemy class.
 *
 * @author Juyoung Lee, Sungmn Lee
 */
#include "enemy.h"

// Static variable for tracking total enemy deaths
int Enemy::totalDeath = 0;

/**
 * Constructs an Enemy with specified starting position and screen parameters.
 *
 *
 * @param startX Initial X position.
 * @param startY Initial Y position.
 * @param screenWidth Width of the screen for calculating movement boundaries.
 * @param resolution Screen resolution for sprite scaling.
 */
Enemy::Enemy(float startX, float startY, unsigned int screenWidth, const sf::Vector2u& resolution)
        : movementSpeed(3.0f), screenWidth(screenWidth),isAlive(true) {
    setPosition(startX, startY);
    res1.x = resolution.x;
    res1.y = resolution.y;

    sprite.setScale(1.f * ((float)resolution.x/1280.f), 1.f * ((float)resolution.y/720.f));
    movementSpeed *= (1.0f * ((float)resolution.x/1280.f));
}

/**
 * Marks the enemy as killed and increments the total death count.
 *
 */
void Enemy::kill() {
    isAlive = false;
    totalDeath++;
    std::cout << "Enemy killed. Total deaths: " << totalDeath << std::endl;
}

/**
 * Updates the enemy's position and its bullets' positions.
 *
 *
 * @param deltaTime Time elapsed since the last update, used for consistent movement speed.
 */
void Enemy::update(const sf::Time& deltaTime) {
    float moveDistance = movementSpeed * deltaTime.asSeconds();
    sprite.move(moveDistance, 0);
    if (sprite.getPosition().x > screenWidth) {
        sprite.setPosition(-sprite.getGlobalBounds().width, sprite.getPosition().y);
    }
    // Update the position of enemy bullets
    for (auto& bullet : bullets) {
        bullet.update(deltaTime,"enemy");
    }
    //if bullet goes off screen
    removeBullet();
}

/**
 * Draws the enemy and its bullets to the specified window.
 *
 * @param window The SFML window to draw onto.
 */
void Enemy::draw(sf::RenderWindow& window) {
    if (isAlive) {
        window.draw(sprite);
    }
    // Draw enemy bullets on the screen
    for (auto& bullet : bullets) {
        bullet.draw(window, "enemy");
    }
}

/**
 * Sets the texture of the enemy sprite from a given file path.
 *
 * @param texturePath Path to the texture file.
 */
void Enemy::setTexture(const std::string& texturePath) {
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
}

/**
 * Gets the global bounds of the enemy's sprite.
 *
 * @return A sf::FloatRect representing the global bounds of the sprite.
 */
sf::FloatRect Enemy::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

/**
 * Gets the size of the enemy's texture.
 *
 *
 * @return A sf::Vector2u representing the width and height of the texture.
 */
sf::Vector2u Enemy::getSize() const {
    return texture.getSize();
}

/**
 * Checks if the enemy is currently alive.
 *
 *
 * @return True if the enemy is alive, otherwise false.
 */
bool Enemy::getIsAlive() const {
    return isAlive; // Assuming 'isAlive' is a boolean member variable indicating the alive status.
}

/**
 * Triggers the enemy to shoot, creating and storing a new bullet.
 *
 * This function instantiates a bullet at the enemy's current position, adding it to
 * the vector of bullets that the enemy has shot. Bullets are used for player-enemy interactions.
 */
void Enemy::shoot() {
    // Create a new bullet at the position of the enemy
    Bullet enemyBullet(getPosition().x, getPosition().y, "enemy", res1);
    bullets.push_back(enemyBullet);
}

/**
 * Provides access to the bullets shot by the enemy.
 *
 *
 * @return A reference to a std::vector of Bullet objects representing the enemy's shots.
 */
std::vector<Bullet>& Enemy::getBullets() {
    return bullets;
}

/**
 * Sets the enemy's alive status.
 *
 * @param alive The new alive status of the enemy.
 */
void Enemy::setIsAlive(bool alive) {
    isAlive = alive;
}


/**
 * Increases the movement speed of the enemy by a given factor.
 *
 * @param factor The multiplicative factor to increase the enemy's speed by.
 */
void Enemy::increaseSpeed(float factor) {
    movementSpeed *= factor;
}

/**
 * Removes bullets that have moved off the screen.
 */
void Enemy::removeBullet() {
    for (int i = bullets.size() - 1; i >= 0; --i) {
        if (bullets[i].getGlobalBounds().getPosition().x > res1.x) {
            bullets.erase(bullets.begin() + i);
        }
    }
}
