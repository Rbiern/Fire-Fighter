//Sungmin Lee

#include "player.h"

/**
 * constructor of player
 * @param startX Starting point in x coordinate
 * @param startY Starting point in y coordinate
 */
Player::Player(float startX, float startY,  const sf::Vector2u& resolution): Entity() {
    this->setPosition(startX, startY);
    movementSpeed = 3.0f;
    //water-drop sound effect
    if (!shootBuffer.loadFromFile("../../resource/sounds/water-drop.mp3")) {
        std::cerr << "Shoot sound could not be loaded" << std::endl;
    }
    shootSound.setBuffer(shootBuffer);
    options = new Settings();
    lives = 3;

    sprite.setScale(options->widthScaling(1.5f), options->heightScaling(1.5f));
    movementSpeed *= options->widthScaling(1.5f);
}

//move player's bulletSprite
void Player::move(const sf::Vector2f& direction) {
    sprite.move(direction * movementSpeed);
}
/**
 * draw player on the window
 * @param window window
 */
void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
/**
 * set the number of player's life
 * @param lives
 */
void Player::setLives(int lives) {
    this->lives = lives;
}
/**
 * get the number of player's life
 * @return number of lives player has
 */
int Player::getLives() const {
    return lives;
}
/**
 * decrease player's lives by 1
 */
void Player::decreaseLife() {
    if (lives > 0) {
        --lives;
    }
}
/**
 * increase player's lives by 1
 */
void Player::increaseLife() {
    if (lives < 3) {
        ++lives;
    }
}

/**
 * set player's movement speed
 * @param speed movement speed
 */
void Player::setSpeed(float speed) {
    movementSpeed = speed;
}

/**
 * get player's movement speed
 * @return player's movement speed
 */
float Player::getSpeed() const {
    return movementSpeed;
}
/**
 * check player has collide with enemy
 * @param enemySprite enemy's bulletSprite
 * @return true if player collide with enemy
 */
bool Player::isCollidingWithEnemy(const sf::Sprite& enemySprite) const {
    // Check if the x positions overlap
    return playerBounds.left < enemyBounds.left + enemyBounds.width &&
           playerBounds.left + playerBounds.width > enemyBounds.left;

}
/**
 * get size of player's bulletSprite
 * @return size of player's bulletSprite
 */
sf::Vector2f Player::getSize() const {
    return sprite.getGlobalBounds().getSize();
}
/**
 * player's ability to shoot the water
 */
void Player::shoot() {
    //new bullet's starting posiiton
    Bullet newBullet(getPosition().x - getSize().x / 2, getPosition().y + getSize().y / 2, "player", options->getVector());
    bullet.push_back(newBullet);
    if (options->toggleSounds()) {
        shootSound.play();
    }
}
/**
 * update bullets by time
 * @param delta time
 */
void Player::updateBullets(const sf::Time& delta, EnemyWave& enemyWave, Metrics& metrics) {
    for (auto& bullet : bullet) {
        bullet.update(delta, "player");
    }
    auto bulletIt = bullet.begin();
    while (bulletIt != bullet.end()) {
        bool bulletRemoved = false;
        for (int i = 0; i < enemyWave.getRows() && !bulletRemoved; ++i) {
            for (int j = 0; j < enemyWave.getColumns() && !bulletRemoved; ++j) {
                Enemy& enemy = enemyWave.getEnemy(i, j);
                if (enemy.getIsAlive() && bulletIt->getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                    enemy.kill();
                    metrics.increaseScore(10);
                    bulletIt = bullet.erase(bulletIt);
                    bulletRemoved = true;
                }
            }
        }
        if (!bulletRemoved) {
            ++bulletIt;
        }
    }
}
/**
 * Updates the bullets for collisions with barriers and shrinks the barrier upon collision.
 * @param delta time
 * @param barrier barrier
 * @param resolution resolution
 */
void Player::updateBarrier(const sf::Time delta, Barrier& barrier) {
    for (auto bulletIt = bullet.begin(); bulletIt != bullet.end();) {
        bulletIt->update(delta, "player");

        if (barrier.bulletCollision(bulletIt->getSprite())) {
            bulletIt = bullet.erase(bulletIt);
            barrier.shrink();
        }
        else {
            ++bulletIt;
        }
    }
}
/**
 * Draws all bullets shot by the player on the specified render window.
 * @param window
 */
void Player::drawBullets(sf::RenderWindow& window) {
    for (auto& bullet : bullet) {
        bullet.draw(window,"player");
    }
}
/**
 * Destructor that cleans up resources, specifically deleting any dynamically allocated memory to prevent memory leaks.
 */
Player::~Player() {
    delete options;
}

/**
 * Sets the texture of the player's bulletSprite based on the provided file path.
 * @param str file path
 */
void Player::setPlayerTexture(char* str) {
    this->setTexture(str);
}

/**
 * reset player's position and lives
 */
void Player::reset() {
    setLives(3);
    setPosition(options->getResolution()[0]* 0.93f ,options->getResolution()[1] / 2);
}
