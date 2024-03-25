// Enemy.cpp
#include "Enemy.h"
#include <cmath>

Enemy::Enemy(float startX, float startY, unsigned int screenWidth)
        : movementSpeed(5.0f), screenWidth(screenWidth) {
    setPosition(startX, startY);
}

void Enemy::update(const sf::Time& deltaTime) {
    float moveDistance = movementSpeed * deltaTime.asSeconds();
    sprite.move(moveDistance, 0);
    if (sprite.getPosition().x > screenWidth) {
        sprite.setPosition(-sprite.getGlobalBounds().width, sprite.getPosition().y);
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
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

sf::Vector2u Enemy::getSize() const {
    return texture.getSize();
}

EnemyWave::EnemyWave(sf::RenderWindow& window)
        : waveAmplitude(20.0f), waveFrequency(0.5f), wavePhase(0.0f),
          rows(4), columns(10), spacingX(100.0f), spacingY(70.0f),
          startX(-900.0f), startY(75.0f) {
    enemyGrid.resize(rows, std::vector<Enemy>(columns, Enemy(0, 0, window.getSize().x)));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            float positionX = startX + j * spacingX;
            float positionY = startY + i * spacingY;
            enemyGrid[i][j] = Enemy(positionX, positionY, window.getSize().x);
            enemyGrid[i][j].setTexture("../../resource/img/fire.png");
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
