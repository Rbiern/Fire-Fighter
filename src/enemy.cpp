#include "enemy.h"


Enemy::Enemy(float startX, float startY, unsigned int screenWidth, const sf::Vector2u& resolution)
        : movementSpeed(3.0f), screenWidth(screenWidth),isAlive(true) {
    setPosition(startX, startY);
    res1.x = resolution.x;
    res1.y = resolution.y;

    sprite.setScale(1.f * ((float)resolution.x/1280.f), 1.f * ((float)resolution.y/720.f));
    movementSpeed *= (1.0f * ((float)resolution.x/1280.f));
}


int Enemy::totalDeath = 0;

void Enemy::kill() {
    isAlive = false;
    totalDeath++;
    std::cout << "Enemy killed. Total deaths: " << totalDeath << std::endl;
}

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

void Enemy::draw(sf::RenderWindow& window) {
    if (isAlive) {
        window.draw(sprite);
    }
    // Draw enemy bullets on the screen
    for (auto& bullet : bullets) {
        bullet.draw(window, "enemy");
    }
}

void Enemy::setTexture(const std::string& texturePath) {
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
}



sf::FloatRect Enemy::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}


sf::Vector2u Enemy::getSize() const {
    return texture.getSize();
}

bool Enemy::getIsAlive() const {
    return isAlive; // Assuming 'isAlive' is a boolean member variable indicating the alive status.
}

void Enemy::shoot() {
    // Create a new bullet at the position of the enemy
    Bullet enemyBullet(getPosition().x, getPosition().y, "enemy", res1);
    bullets.push_back(enemyBullet);
}

std::vector<Bullet>& Enemy::getBullets() {
    return bullets;
}

void Enemy::setIsAlive(bool alive) {
    isAlive = alive;
}

void Enemy::increaseSpeed(float factor) {
    movementSpeed *= factor;
}
void Enemy::removeBullet() {
    for (int i = bullets.size() - 1; i >= 0; --i) {
        if (bullets[i].getGlobalBounds().getPosition().x > res1.x) {
            bullets.erase(bullets.begin() + i);
        }
    }
}
