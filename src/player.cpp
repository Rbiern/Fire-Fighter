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
    options = new settings();
    lives = 3;
    adjustForResolution(resolution);
}

//move player's sprite
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
 * @param enemySprite enemy's sprite
 * @return true if player collide with enemy
 */
bool Player::isCollidingWithEnemy(const sf::Sprite& enemySprite) const {
    return sprite.getGlobalBounds().intersects(enemySprite.getGlobalBounds());
}
/**
 * get size of player's sprite
 * @return size of player's sprite
 */
sf::Vector2f Player::getSize() const {
    return sprite.getGlobalBounds().getSize();
}
/**
 * player's ability to shoot the water
 */
void Player::shoot() {
    //new bullet's starting posiiton
    Bullet newBullet(getPosition().x - getSize().x / 2, getPosition().y + getSize().y / 2, "player");
    bullets.push_back(newBullet);
    if (options->toggleSounds()) {
        shootSound.play();
    }
}
/**
 * update bullets by time
 * @param delta time
 */
void Player::updateBullets(const sf::Time& delta, EnemyWave& enemyWave, Metrics& metrics) {
    for (auto& bullet : bullets) {
        bullet.update(delta, "player");
    }
    auto bulletIt = bullets.begin();
    while (bulletIt != bullets.end()) {
        bool bulletRemoved = false;
        for (int i = 0; i < enemyWave.getRows() && !bulletRemoved; ++i) {
            for (int j = 0; j < enemyWave.getColumns() && !bulletRemoved; ++j) {
                Enemy& enemy = enemyWave.getEnemy(i, j);
                if (enemy.getIsAlive() && bulletIt->getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                    enemy.kill();
                    metrics.increaseScore(10);
                    bulletIt = bullets.erase(bulletIt);
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
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bulletIt->update(delta, "player");

        if (barrier.bulletCollision(bulletIt->getSprite())) {
            bulletIt = bullets.erase(bulletIt);
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
    for (auto& bullet : bullets) {
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
 * Sets the texture of the player's sprite based on the provided file path.
 * @param str file path
 */
void Player::setPlayerTexture(char* str) {
    this->setTexture(str);
}
/**
 * Adjusts the player's scale and speed based on the game's resolution to ensure consistent gameplay across different resolutions.
 * @param resolution array of resolution
 */
void Player::adjustForResolution(const sf::Vector2u& resolution) {
    float scale = 1.0f;
    float speedScale = 1.0f;

    if (resolution == sf::Vector2u(640, 360)) {
        scale = 1.0f;
        speedScale = 1.00f;
    } else if (resolution == sf::Vector2u(1280, 720)) {
        scale = 1.5f;
        speedScale = 1.5f;
    } else if (resolution == sf::Vector2u(1920, 1080)) {
        scale = 2.0f;
        speedScale = 1.75f;
    } else if (resolution == sf::Vector2u(3840, 2160)) {
        scale = 2.6f;
        speedScale = 2.0f;
    }

    sprite.setScale(scale, scale);

    movementSpeed *= speedScale;
}
/**
 * Sets the scale of the player's sprite to a specified factor.
 * @param scaleFactor scale factor
 */
void Player::setScale(float scaleFactor) {
    sprite.setScale(scaleFactor, scaleFactor);
}
