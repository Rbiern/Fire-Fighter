// Enemy.cpp
#include "Enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(float startX, float startY, unsigned int screenWidth, const sf::Vector2u& resolution)
        : movementSpeed(5.0f), screenWidth(screenWidth),isAlive(true) {
    setPosition(startX, startY);
    adjustForResolution(resolution);
}

int Enemy::totalDeath = 0;

void Enemy::kill() {
    isAlive = false;
    totalDeath++;
    std::cout << "Enemy killed. Total deaths: " << totalDeath << std::endl;
}

int Enemy::getTotalDeath() {
    return totalDeath;
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
}

void Enemy::draw(sf::RenderWindow& window) {
    if (isAlive) {
        window.draw(sprite);
        // Draw enemy bullets on the screen
        for (auto& bullet : bullets) {
            bullet.draw(window);
        }
    }
}

void Enemy::setTexture(const std::string& texturePath) {
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
}

sf::Vector2f Enemy::getPosition() const {
    return sprite.getPosition();
}


void Enemy::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}
void Enemy::adjustForResolution(const sf::Vector2u& resolution) {
    float scale = 1.0f;
    float speedScale = 1.0f;

    if (resolution == sf::Vector2u(640, 360)) {
        scale = 0.5f;
        speedScale = 1.00f;
    } else if (resolution == sf::Vector2u(1280, 720)) {
        scale = 1.0f;
        speedScale = 1.5f;
    } else if (resolution == sf::Vector2u(1920, 1080)) {
        scale = 1.5f;
        speedScale = 1.75f;
    } else if (resolution == sf::Vector2u(3840, 2160)) {
        scale = 2.0f;
        speedScale = 2.0f;
    }

    sprite.setScale(scale, scale);

    movementSpeed *= speedScale;
}
sf::FloatRect Enemy::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
void EnemyWave::removeEnemy(int row, int column) {
    // Remove enemy at specified position
    enemyGrid[row].erase(enemyGrid[row].begin() + column);
}

sf::Vector2u Enemy::getSize() const {
    return texture.getSize();
}

void EnemyWave::adjustSpacingForResolution(const sf::Vector2u& resolution) {
    if (resolution == sf::Vector2u(640, 360)) {
        spacingX = 70.0f; // Smaller resolution, reduce spacing
        spacingY = 40.0f;
    } else if (resolution == sf::Vector2u(1280, 720)) {
        spacingX = 100.0f; // Base resolution, base spacing
        spacingY = 70.0f;
    } else if (resolution == sf::Vector2u(1920, 1080)) {
        spacingX = 130.0f; // Higher resolution, increase spacing
        spacingY = 90.0f;
    } else if (resolution == sf::Vector2u(3840, 2160)) {
        spacingX = 160.0f; // 4K resolution, further increase spacing
        spacingY = 110.0f;
    } else {
        // Default case for resolutions not explicitly handled
        // Optionally adjust based on resolution dimensions, or keep base values
    }
}
EnemyWave::EnemyWave(sf::RenderWindow& window, const sf::Vector2u& resolution)
        : waveAmplitude(20.0f), waveFrequency(0.5f), wavePhase(0.0f),
          rows(8), columns(4), spacingX(100.0f), spacingY(70.0f),
          startX(200.0f), startY(75.0f) {
    adjustSpacingForResolution(resolution); // Adjust spacing based on resolution
    enemyGrid.resize(rows, std::vector<Enemy>(columns, Enemy(0, 0, window.getSize().x, resolution)));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            float positionX = startX + j * spacingX;
            float positionY = startY + i * spacingY;
            enemyGrid[i][j] = Enemy(positionX, positionY, window.getSize().x, resolution);
            enemyGrid[i][j].setTexture("../../resource/img/fire.png");
            totalSpawned++;
        }
    }
}

void EnemyWave::update(sf::Time deltaTime) {
    wavePhase += deltaTime.asSeconds();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            float waveOffset = sin(wavePhase + j * waveFrequency) * waveAmplitude;
            enemyGrid[i][j].setPosition(enemyGrid[i][j].getPosition().x, startY + i * spacingY + waveOffset);
            enemyGrid[i][j].update(deltaTime);
        }
    }
}

void EnemyWave::draw(sf::RenderWindow& window) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            enemyGrid[i][j].draw(window);
        }
    }
}

Enemy& EnemyWave::getEnemy(int row, int column) {
    return enemyGrid[row][column];
}

int EnemyWave::getRows() const {
    return rows;
}

int EnemyWave::getColumns() const {
    return columns;
}
bool Enemy::getIsAlive() const {
    return isAlive; // Assuming 'isAlive' is a boolean member variable indicating the alive status.
}

void Enemy::shoot() {
    // Create a new bullet at the position of the enemy
    Bullet enemyBullet(getPosition().x, getPosition().y, "enemy");
    bullets.push_back(enemyBullet);
}

std::vector<Bullet>& Enemy::getBullets() {
    return bullets;
}

const sf::Sprite& Enemy::getSprite() const {
    return sprite;
}
