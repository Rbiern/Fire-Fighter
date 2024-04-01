// Enemy.cpp
#include "enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(float startX, float startY, unsigned int screenWidth, const sf::Vector2u& resolution)
        : movementSpeed(3.0f), screenWidth(screenWidth),isAlive(true) {
    setPosition(startX, startY);
    adjustForResolution(resolution);
    res1.x = resolution.x;
    res1.y = resolution.y;
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
        scale = 0.3f;
        speedScale = 0.5f;
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
EnemyWave::EnemyWave(sf::RenderWindow& window, const sf::Vector2u& resolution, float metricsBarHeight)
        : window(window),waveAmplitude(20.0f), waveFrequency(0.5f), wavePhase(0.0f),
          rows(5), columns(4), spacingX(100.0f), spacingY(70.0f),
          startX(0.0f),  startY(75.0f + metricsBarHeight) {
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

void EnemyWave::update(sf::Time deltaTime, float metricsBarHeight) {
    float screenLimit = window.getSize().y - metricsBarHeight;
    float moveRightDistance = 50.0f;
    static bool movingDown = true;
    static bool hasMovedRightAfterReach = false;
    static bool firstUpdate = true;

    bool bottomReached = false;
    bool topReached = false;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            Enemy& enemy = enemyGrid[i][j];
            if (enemy.getPosition().y + enemy.getGlobalBounds().height > window.getSize().y) {
                bottomReached = true;
                break;
            }
            if (enemy.getPosition().y <= metricsBarHeight) {
                topReached = true;
                break;
            }
        }
        if (bottomReached || topReached) break;
    }

    if (firstUpdate) {
        movingDown = true;
        firstUpdate = false;
    } else if ((bottomReached || topReached) && !hasMovedRightAfterReach) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                Enemy& enemy = enemyGrid[i][j];
                enemy.setPosition(enemy.getPosition().x + moveRightDistance, enemy.getPosition().y);
            }
        }
        hasMovedRightAfterReach = true;
        movingDown = !movingDown;
    } else {
        float moveDistance = movingDown ? 1 : -1;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                Enemy& enemy = enemyGrid[i][j];
                enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y + moveDistance);
            }
        }
        if (hasMovedRightAfterReach && (bottomReached || topReached)) {
            hasMovedRightAfterReach = false;
        }
    }
}







//void EnemyWave::update(sf::Time deltaTime, float metricsBarHeight) {
//    wavePhase += deltaTime.asSeconds();
//    float screenLimit = window.getSize().y - metricsBarHeight; // Calculate screen limit considering metrics bar
//    for (int i = 0; i < rows; ++i) {
//        for (int j = 0; j < columns; ++j) {
//            float waveOffset = sin(wavePhase + j * waveFrequency) * waveAmplitude;
//            float newPositionY = startY + i * spacingY + waveOffset;
//            if (newPositionY + enemyGrid[i][j].getGlobalBounds().height > screenLimit) {
//                newPositionY = screenLimit - enemyGrid[i][j].getGlobalBounds().height; // Adjust position to stay within screen
//            }
//            enemyGrid[i][j].setPosition(enemyGrid[i][j].getPosition().x, newPositionY);
//            // No change to the horizontal movement logic
//        }
//    }
//}

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
    Bullet enemyBullet(getPosition().x, getPosition().y, "enemy", res1);
    bullets.push_back(enemyBullet);
}

std::vector<Bullet>& Enemy::getBullets() {
    return bullets;
}

const sf::Sprite& Enemy::getSprite() const {
    return sprite;
}

bool EnemyWave::allEnemiesDead() const {
    for (const auto& row : enemyGrid) {
        for (const auto& enemy : row) {
            if (enemy.getIsAlive()) {
                return false; // If any enemy is alive, return false
            }
        }
    }
    return true; // All enemies are dead
}

void EnemyWave::respawnEnemies() {
    float speedIncreaseFactor = 2.0f; //enemy speed increase factor
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            float positionX = startX + j * spacingX;
            float positionY = startY + i * spacingY;
            enemyGrid[i][j].setPosition(positionX, positionY);
            enemyGrid[i][j].setIsAlive(true);
            enemyGrid[i][j].increaseSpeed(speedIncreaseFactor);
        }
    }
}
void Enemy::setIsAlive(bool alive) {
    isAlive = alive;
}

void Enemy::increaseSpeed(float factor) {
    movementSpeed *= factor;
}
