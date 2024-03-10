#include "player.h"

Player::Player(float startX, float startY) {
    loadTexture("/Users/charlie/cs3307Ass/group19/resource/img/water.png");
    sprite.setPosition(startX, startY);
    movementSpeed = 0.5f; // 기본 이동 속도 설정
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::move(const sf::Vector2f& direction) {
    sprite.move(direction * movementSpeed);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::setSpeed(float speed) {
    movementSpeed = speed;
}

float Player::getSpeed() const {
    return movementSpeed;
}
sf::Vector2f Player::getSize() const {
    return sprite.getGlobalBounds().getSize();
}

