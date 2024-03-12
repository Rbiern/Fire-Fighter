//Sungmin Lee

#include "player.h"

/**
 * constructor of player
 * @param startX Starting point in x coordinate
 * @param startY Starting point in y coordinate
 */
Player::Player(float startX, float startY) : Entity() {
    this->setTexture("../../resource/img/waterBoy.png");
    this->setPosition(startX, startY);
    movementSpeed = 3.0f;
    //water-drop sound effect
    if (!shootBuffer.loadFromFile("../../resource/sounds/water-drop.mp3")) {
        std::cerr << "Shoot sound could not be loaded" << std::endl;
    }
    shootSound.setBuffer(shootBuffer);
    options = new settings();
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
    Bullet newBullet(getPosition().x - getSize().x / 2, getPosition().y + getSize().y / 2);
    bullets.push_back(newBullet);
    if (options->toggleSounds()) {
        shootSound.play();
    }
}
/**
 * update bullets by time
 * @param delta time
 */
void Player::updateBullets(const sf::Time& delta) {
    for (auto& bullet : bullets) {
        bullet.update(delta);
    }

    // delete bullets gone off screen
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](const Bullet& bullet) {
        return bullet.getPosition().x < 0;
    }), bullets.end());
}

void Player::drawBullets(sf::RenderWindow& window) {
    for (auto& bullet : bullets) {
        window.draw(bullet.getSprite());
    }
}
Player::~Player() {

}
